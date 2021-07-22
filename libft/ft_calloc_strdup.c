/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_strdup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <...@student.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 13:29:51 by wnormcor          #+#    #+#             */
/*   Updated: 2020/05/08 10:33:19 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	result = NULL;
	result = malloc(count * size);
	if (result == NULL)
		return (NULL);
	ft_bzero(result, count * size);
	return (result);
}

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*rp;

	size = ft_strlen(s) + 1;
	if ((rp = malloc(size)) == NULL)
		return (NULL);
	while (size-- != 0)
		rp[size] = s[size];
	return (rp);
}
