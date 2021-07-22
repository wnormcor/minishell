/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sec_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <...@student.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:10:50 by wnormcor          #+#    #+#             */
/*   Updated: 2020/05/08 11:14:46 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	char	*wp;

	if (s == NULL)
		return (NULL);
	if ((res = malloc(len + 1)) == NULL)
		return (NULL);
	wp = res;
	while (start != 0 && *s != '\0')
	{
		start--;
		s++;
	}
	while (len != 0 && *s != '\0')
	{
		*wp++ = *s++;
		len--;
	}
	*wp = '\0';
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*res;
	char	*wp;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = 1 + ft_strlen(s1);
	size += ft_strlen(s2);
	if ((res = malloc(size)) == NULL)
		return (NULL);
	wp = res;
	while (*s1 != '\0')
		*wp++ = *s1++;
	while (*s2 != '\0')
		*wp++ = *s2++;
	*wp = '\0';
	return (res);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*res;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (*s1 != '\0' && ft_strchr(set, *s1) != NULL)
		s1++;
	len = ft_strlen(s1);
	while (len != 0 && ft_strrchr(set, s1[len - 1]) != NULL)
		len--;
	if ((res = ft_substr(s1, 0, len)) == NULL)
		return (NULL);
	return (res);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			len;
	char			*res;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	if ((res = malloc(len + 1)) == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = (*f)(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
