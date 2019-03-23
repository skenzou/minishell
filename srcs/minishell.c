/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 09:15:55 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/23 18:26:25 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv)
{
  pid_t father;
  int a;
  char *input;
  int ret;

  ret = 1;
  while (ret == 1)
  {
    if ((ret = get_next_line(0, &input)) > 0)
    {
      father = fork();
      if (father > 0)
        wait(&a);
      if (father == 0)
        execve(input, argv, NULL);
    }
  }
  (void)argc;
    // father = fork();
    // if (father > 0)
    //   wait(&a);
    //
    // if (father == 0)
    //     execve("/bin/ls", argv, NULL);
}
