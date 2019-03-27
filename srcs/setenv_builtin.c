/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 18:46:30 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/27 21:02:46 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int   is_set(char *key, char **env)
{
  int i;
  int len;

  i = -1;
  len = ft_strlen(key);
  while (env && env[++i])
  {
    if (!ft_strncmp(key, env[i], len))
      return (i);
  }
  return (-1);
}

static char  **addkey(char *key, char *value, char **env)
{
  int i;
  char **fresh_env;
  int count;

  count = ft_split_count(env);
  fresh_env = (char **)ft_memalloc(sizeof(char *) * (count + 2));
  fresh_env == NULL ? exit(1) : 0;
  i = -1;
  while (++i < count)
    if (!(fresh_env[i] = ft_strdup(env[i])))
      exit(1);
  fresh_env[i] = !value ? key : ft_strjoin(key, value);
  fresh_env[i] == NULL ? exit(1) : 0;
  fresh_env[i + 1] = NULL;
  ft_splitdel(env);
  return (fresh_env);
}

int   setenv_builtin(int ac, char **av, char ***env)
{
  int i;
  char *temp;
  char *key;

  if (ac > 3)
    return (SETENV_USG);
  if (ac == 1)
  {
      print_env(*env);
      return (0);
  }
  key = ft_strjoin(av[1], "=");
  key == NULL ? exit(1) : 0;
  i = is_set(key, *env);
  if (i >= 0)
  {
    temp = (*env)[i];
    (*env)[i] = ac == 2 ? key : ft_strjoin(key, av[2]);
    (*env)[i] == NULL ? exit(1) : 0;
    ft_strdel(&temp);
  }
  else
    *env = ac == 2 ? addkey(key, NULL, *env) : addkey(key, av[2], *env);
  ac == 3 ? ft_strdel(&key) : 0;
  return (0);
}
