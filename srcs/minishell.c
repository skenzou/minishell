/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 09:15:55 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/23 22:52:17 by midrissi         ###   ########.fr       */
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

int		main(int argc, char **argv, char **env)
{
	pid_t	father;
	// int		a;
	char	*input;
	int		ret;
	char	**args;

	ret = 1;
	int i = -1;
	while (env[++i] != NULL)
		ft_printf("%s\n", env[i]);
	print_curr_dir();
	while (ret == 1)
	{
		if ((ret = get_next_line(0, &input)) > 0)
		{
			father = fork();
			if (father > 0)
			{
				wait(&father);
				print_curr_dir();
			}
			if (father == 0)
			{
				args = ft_strsplit(input, ' ');
				execve(args[0], args, NULL);
			}
		}
	}
	(void)argc;
	(void)argv;
}
