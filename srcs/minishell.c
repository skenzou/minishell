/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 09:15:55 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/24 22:50:22 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 		print_env(char **env)
{
	int i;

	i = -1;
	while (env && env[++i])
		ft_printf("%s\n", env[i]);
}

void	print_curr_dir(void)
{
	char	buff[MAX_PATH_LEN];
	int		i;
	int		j;

	i = -1;
	j = 0;
	ft_bzero(buff, MAX_PATH_LEN);
	getcwd(buff, MAX_PATH_LEN);
	while (buff[++i])
		if (buff[i] == '/' && buff[i + 1])
			j = i + 1;
	ft_printf(ANSI_BLUE "-> " ANSI_RESET);
	ft_printf(ANSI_CYAN "%s" ANSI_RESET, buff + j);
	ft_printf(ANSI_BLUE "> "ANSI_RESET);
}

int		is_path(char *str)
{
	while (*str)
	{
		if (*str == '/')
			return (1);
		str++;
	}
	return (0);
}

char	*get_env_path(char **env)
{
	int	i;

	i = -1;
	while (env && env[++i])
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (env[i] + 5);
	return (NULL);
}

void		set_path(char fullpath[], char *cmd, char *path)
{
	ft_bzero(fullpath, MAX_PATH_LEN);
	ft_strcpy(fullpath, path);
	ft_strcat(fullpath, "/");
	ft_strcat(fullpath, cmd);
}

int		find_bin(char **bin, char **env, char **paths)
{
	char path[MAX_PATH_LEN];
	struct stat buff;
	pid_t		pid;
	int i;

	i = -1;
	while (paths && paths[++i])
	{
			set_path(path, bin[0], paths[i]);
			if (!lstat(path, &buff))
				if (!access(path, X_OK))
				{
					pid = fork();
					signal(SIGINT, sigfork);
					if (!pid)
						execve(path, bin, env);
					wait(&pid);
					return (1);
				}
	}
	return (0);
}

int		exec_envpath(char **bin, char **env)
{
	char *paths;
	char **split_paths;

	if ((paths = get_env_path(env)) == NULL || paths[0] == '\0')
		split_paths = NULL;
	else
		split_paths = ft_strsplit(paths, ':');
	if (find_bin(bin, env, split_paths) == 0)
		ft_printf("-minishell: %s: command not found\n", bin[0]);
	ft_splitdel(split_paths);
	return (0);
}

int	exec_binpath(char **bin, char **env)
{
	struct stat	buff;
	pid_t				pid;

	if (lstat(bin[0], &buff) == -1)
		return (NON_EXISTENT);
	if (S_ISREG(buff.st_mode) == 1 && !access(bin[0], X_OK))
	{
		pid = fork();
		signal(SIGINT, sigfork);
		if (pid == 0)
			execve(bin[0], bin, env);
		else if (pid < 0)
			return (FAILFORK);
		wait(&pid);
	}
	else if (access(bin[0], X_OK) != 0)
		return (NO_RIGHT);
	else if (S_ISDIR(buff.st_mode) == 1)
		return (IS_DIRECTORY);
	return (0);
}

void 	exec_bin(char **bin, char **env)
{
	int err;

	if (is_path(bin[0]))
		err = exec_binpath(bin, env);
	else
		err = exec_envpath(bin, env);
	if (err)
		err_handler(err, bin[0]);
}

int		get_builtin(char *cmd)
{
	if (ft_strequ(cmd, "echo") == 1)
		return (ECHO);
	else if (ft_strequ(cmd, "cd") == 1)
		return (CD);
	else if (ft_strequ(cmd, "setenv") == 1)
		return (SETENV);
	else if (ft_strequ(cmd, "unsetenv") == 1)
		return (UNSETENV);
	else if (ft_strequ(cmd, "env") == 1)
		return (ENV);
	else if (ft_strequ(cmd, "exit") == 1)
		return (EXIT);
return (0);
}

void	exec_builtin(char **builtin, int id, char **env)
{
	int	ac;
	int	err_id;

	ac = ft_split_count(builtin);
	err_id = 0;
	if (id == ECHO)
		err_id = echo_builtin(ac, builtin);
	if (id == CD)
		err_id = cd_builtin(ac, builtin, env);
	if (id == ENV && ac == 1)
		print_env(env);
	if (id == EXIT)
		exit_builtin();
	if (err_id != 0)
		err_handler(err_id, builtin[0]);
}

int 		cmd_handler(char *cmd, char **env)
{
	char **args;
	int id;

	args = ft_strsplit(cmd, ' ');
	if (!ft_split_count(args))
		return (0);
	if (!args)
		return (-1);
	id = get_builtin(args[0]);
	if (id > 0)
		exec_builtin(args, id, env);
	else
		exec_bin(args, env);
	ft_splitdel(args);
	return (0);
}

void 		input_handler(char *input,char **env)
{
	int i;
	int ret;
	char **cmds;

	cmds = ft_strsplit(input, ';');
	ft_strdel(&input);
	if (!cmds)
	{
			ft_splitdel(env);
			exit(0);
	}
	i = -1;
	while (cmds[++i])
	{
			ret = cmd_handler(cmds[i], env);
			if (ret == -1)
			{
				ft_splitdel(cmds);
				ft_splitdel(env);
				exit(0);
			}
	}
	ft_splitdel(cmds);
}

char **dup_env(char **env)
{
	char **p;
	int i;

	i = ft_split_count(env);
	if (!(p = (char **)ft_memalloc(sizeof(char *) * (i + 1))))
		exit(0);
	i = -1;
	while (env[++i])
		if (!(p[i] = ft_strdup(env[i])))
			exit(0);
	p[i] = NULL;
	return (p);
}

int main(int argc, char **argv, char **env)
{
	char *input;
	int ret;

	ret = 1;
	env = dup_env(env);
	while (ret == 1)
	{
		print_curr_dir();
		signal(SIGINT, sighandler);
		if ((ret = get_next_line(0, &input)) > 0)
			input_handler(input, env);
		if (ret == -1)
			break ;
	}
	(void)argc;
	(void)argv;
	ft_strdel(&input);
	ft_splitdel(env);
	return (0);
}
