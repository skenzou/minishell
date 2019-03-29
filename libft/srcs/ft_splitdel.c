/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitdel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:12:32 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/29 18:16:34 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_splitdel(char **split)
{
	int i;

	i = -1;
	while (split && split[++i])
		ft_strdel(&(split[i]));
	ft_strdel(&(split[i]));
	free(split);
}
