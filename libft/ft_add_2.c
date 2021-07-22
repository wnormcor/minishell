/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 13:09:08 by wnormcor          #+#    #+#             */
/*   Updated: 2021/01/25 16:25:37 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char **s1, char *s2)
{
	char	*new_str;
	size_t	j;
	size_t	i;

	if (!*s1 || !s2)
		return (NULL);
	i = 0;
	j = ft_strlen(*s1) + ft_strlen(s2) + 1;
	if (!(new_str = (char *)malloc(j * sizeof(char))))
		return (NULL);
	j = 0;
	while ((*s1)[i])
		new_str[j++] = (*s1)[i++];
	i = 0;
	while (s2[i])
		new_str[j++] = s2[i++];
	new_str[j] = '\0';
	free(*s1);
	return (new_str);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
