/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 21:38:26 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/24 20:33:14 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# define ANSI_RED		"\x1b[1m\x1b[31m"
# define ANSI_GREEN		"\x1b[1m\x1b[32m"
# define ANSI_YELLOW	"\x1b[1m\x1b[33m"
# define ANSI_BLUE		"\x1b[1m\x1b[34m"
# define ANSI_MAGENTA	"\x1b[1m\x1b[35m"
# define ANSI_CYAN		"\x1b[1m\x1b[36m"
# define ANSI_RESET		"\x1b[0m"
# define MAX_PATH_LEN	4096
// # define EXIT         -1
# define NON_EXISTENT 1
# define IS_DIRECTORY 2
# define NO_RIGHT     3
# define INV_ARG      4
# define SETENV_USG   5
# define UNSETENV_USG 6
# define FAILFORK     7
# define NOT_DIR      8
# define ECHO         9
# define CD           10
# define SETENV       11
# define UNSETENV     12
# define ENV          13
# define EXIT         14

int   cd_builtin(int argc, char **argv, char **env);
void   err_handler(int err_id, char *str);
int     echo_builtin(int argc, char **argv);
void   sigfork(int sig);
void   sighandler(int sig);\
void	print_curr_dir(void);
void    exit_builtin(void);

#endif
