/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sec_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <...@student.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 11:10:14 by wnormcor          #+#    #+#             */
/*   Updated: 2020/05/08 12:19:34 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**checkreturnsplit(char **ls, int cw)
{
	int	i;

	i = 0;
	while (i < cw)
	{
		if (ls[i++] == NULL)
		{
			i = 0;
			while (i < cw)
				free(ls[i++]);
			free(ls);
			return (NULL);
		}
	}
	return (ls);
}

char		**ft_split(char const *s, char c)
{
	int		i;
	int		j1;
	int		j2;
	size_t	count_words;
	char	**array_str;

	i = -1;
	count_words = 0;
	while (s[++i] != '\0')
		if ((i == 0 && s[i] != c) || (s[i] != c && s[i - 1] == c))
			count_words++;
	array_str = ft_calloc(sizeof(char *), (count_words + 1));
	i = 0;
	j1 = -1;
	while (array_str != NULL && count_words-- != 0)
	{
		while (s[++j1] == c)
			;
		j2 = j1;
		while (s[++j2] != c && s[j2] != '\0')
			;
		array_str[i++] = ft_substr(s, j1, j2 - j1);
		j1 = j2;
	}
	return (checkreturnsplit(array_str, i));
}
