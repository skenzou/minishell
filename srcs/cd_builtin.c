/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 11:44:34 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/29 18:02:03 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

static char		*get_homepath(char **env)
{
	int i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "HOME=", 5))
			return (env[i] + 5);
	}
	return (NULL);
}

static char		*get_oldpwd(char **env)
{
	int i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
			return (ft_strdup(env[i] + 7));
	}
	return (NULL);
}

static int		change_dir(char *path, char ***env)
{
	struct stat		buf;
	char			cwd[MAX_PATH_LEN];

	if (path && ft_strlen(path) == 1 && path[0] == '-')
	{
		path = get_oldpwd(*env);
		path == NULL ? exit(1) : 0;
		ft_printf("%s\n", path);
	}
	if (!lstat(path, &buf))
	{
		if (S_ISDIR(buf.st_mode) == 1)
		{
			if (!access(path, X_OK))
			{
				ft_setenv("OLDPWD", getcwd(cwd, sizeof(cwd)), env);
				chdir(path);
				ft_setenv("PWD", getcwd(cwd, sizeof(cwd)), env);
				return (0);
			}
			return (NO_RIGHT);
		}
		return (NOT_DIR);
	}
	return (NON_EXISTENT);
}

int				cd_builtin(int argc, char **argv, char ***env)
{
	char	*path;
	int		err;

	path = NULL;
	err = 0;
	if (argc == 1 && (path = get_homepath(*env)))
		err = change_dir(path, env);
	else if (argc > 1)
		err = change_dir(argv[1], env);
	if (err)
		err_handler(err, path ? path : argv[1]);
	return (0);
}
