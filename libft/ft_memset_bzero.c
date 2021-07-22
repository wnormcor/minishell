/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset_bzero.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <...@student.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 12:30:49 by wnormcor          #+#    #+#             */
/*   Updated: 2020/05/08 12:19:01 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** DESCRIPTION
**   The memset() function fills the first n bytes of the memory area pointed
**   to by s with the constant byte c.
** RETURN VALUE
**   The memset() function returns a pointer to the memory area s.
*/

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char *rs;

	rs = (unsigned char *)s;
	while (n--)
		*(rs++) = (unsigned char)c;
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	char	*target;

	target = s;
	while (n > 0)
	{
		*target = '\0';
		target++;
		n--;
	}
}
