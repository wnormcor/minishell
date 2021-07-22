/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sec_itoa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <...@student.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 10:45:49 by wnormcor          #+#    #+#             */
/*   Updated: 2020/05/08 10:59:06 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*putnbrtostr(char *str, int places, int nbr)
{
	size_t	i;
	int		digit;

	i = 0;
	if (nbr < 0)
		str[i++] = '-';
	while (places != 0)
	{
		digit = nbr / places;
		if (digit < 0)
			digit = -digit;
		str[i++] = digit + '0';
		nbr = nbr % places;
		places /= 10;
	}
	str[i] = '\0';
	return (str);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		des;
	int		nbr;
	int		i;

	nbr = n;
	des = 1;
	i = 1;
	while (n /= 10)
	{
		des *= 10;
		i++;
	}
	if (nbr < 0)
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	str = putnbrtostr(str, des, nbr);
	return (str);
}
