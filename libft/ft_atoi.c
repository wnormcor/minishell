/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <...@student.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 13:24:57 by wnormcor          #+#    #+#             */
/*   Updated: 2020/05/04 09:26:36 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *s)
{
	int		sign;
	long	r;
	int		lend;

	r = 0;
	sign = 1;
	while (*s == 32 || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
		if (*s++ == '-')
			sign = -1;
	lend = 0;
	while (*s >= '0' && *s <= '9' && ++lend)
		r = r * 10 + *s++ - '0';
	if (lend > 19 && sign == -1)
		return (0);
	if (lend > 19 && sign == 1)
		return (-1);
	return (sign * (int)r);
}
