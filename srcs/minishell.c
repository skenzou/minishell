/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 09:15:55 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/24 01:00:39 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_curr_dir(void)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = getcwd(NULL, 0);
	while (str[i])
	{
		if (str[i] == '/' && str[i + 1])
			j = i + 1;
		i++;
	}
	ft_printf(ANSI_CYAN "-> %s$ " ANSI_RESET, str + j);
	ft_strdel(&str);
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

char	**get_paths(char **env)
{
	int i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (ft_strsplit(env[i] + 5, ':'));
	}
	return (NULL);
}

void		set_path(char fullpath[], char *cmd, char *path)
{
	ft_bzero(fullpath, MAX_PATH_LEN);
	ft_strcpy(fullpath, path);
	ft_strcat(fullpath, "/");
	ft_strcat(fullpath, cmd);
}

void		get_bin(char *cmd, char **env, char **args)
{
	char **paths;
	char path[MAX_PATH_LEN];
	struct stat buf;
	int i;

	paths = get_paths(env);
	i = -1;
	while (paths[++i])
	{
			set_path(path, cmd, paths[i]);
			if (!lstat(path, &buf))
			{
				if (!access(path, X_OK))
				{
					execve(path, args, env);
					return ;
				}
			}
	}
}

int		main(int argc, char **argv, char **env)
{
	pid_t	father;
	 int		a;
	char	*input;
	int		ret;
	char	**args;

	ret = 1;
	print_curr_dir();
	while (ret == 1)
	{
		if ((ret = get_next_line(0, &input)) > 0)
		{
			father = fork();
			if (father > 0)
			{
				wait(&a);
				print_curr_dir();
			}
			if (father == 0)
			{
				args = ft_strsplit(input, ' ');
				if (is_path(args[0]))
					execve(args[0], args, env);
				else
				{
						get_bin(args[0], env, args);
				}
			}
		}
	}
	(void)argc;
	(void)argv;
}
