/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 09:15:55 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/22 22:46:17 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv)
{
  pid_t father;
  int a;

  (void)argc;
    father = fork();
    if (father > 0)
      wait(&a);

    if (father == 0)
        execve("/bin/ls", argv, NULL);
}
