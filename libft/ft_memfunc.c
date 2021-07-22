/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memfunc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <...@student.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 08:25:45 by wnormcor          #+#    #+#             */
/*   Updated: 2020/05/04 01:14:51 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *wp;

	if (dest == NULL && src == NULL)
		return (NULL);
	wp = (unsigned char *)dest;
	while (n--)
		*(wp++) = *((unsigned char *)src++);
	return (dest);
}

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char		*dp;
	const unsigned char	*sp;
	unsigned char		chr;

	dp = dest;
	sp = src;
	chr = c;
	while (n-- != 0)
		if ((*dp++ = *sp++) == chr)
			return (dp);
	return (NULL);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*rdest;

	if (dest == NULL && src == NULL)
		return (NULL);
	rdest = dest;
	while ((dest < src) && n--)
		*(char *)dest++ = *(char *)src++;
	while (!(dest < src) && n--)
		((char *)dest)[n] = ((char *)src)[n];
	return (rdest);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;

	p = s;
	while (n-- != 0)
		if (*p++ == (unsigned char)c)
			return ((void *)--p);
	return (NULL);
}

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *p1;
	const unsigned char *p2;

	p1 = s1;
	p2 = s2;
	while (n-- != 0)
		if (*p1++ != *p2++)
			return (*--p1 - *--p2);
	return (0);
}
