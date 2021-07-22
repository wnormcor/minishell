/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 13:09:08 by wnormcor          #+#    #+#             */
/*   Updated: 2021/01/25 16:23:22 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_tmp(void *tmp)
{
	if (tmp != NULL)
	{
		free(tmp);
		tmp = NULL;
	}
}

void	ft_putstr(char *str)
{
	ft_putstr_fd(str, 1);
}

void	ft_free_two_dimensional_arr(char **array)
{
	size_t	i;

	i = -1;
	while (array[++i])
		ft_free_tmp(array[i]);
	free(array);
}

void	ft_lstdelone_f(void *d)
{
	if (d)
	{
		free(d);
		d = NULL;
	}
}
