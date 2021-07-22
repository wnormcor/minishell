/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 00:21:37 by wnormcor          #+#    #+#             */
/*   Updated: 2021/01/30 16:50:53 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin_free(char *s1, char const *s2)
{
	size_t	size;
	char	*res;
	char	*wp;
	char	*tofree;

	if (s1 == NULL)
		return (ft_strdup(s2));
	tofree = s1;
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	if ((res = malloc(size)) == NULL)
	{
		free(tofree);
		return (NULL);
	}
	wp = res;
	while (*s1 != '\0')
		*wp++ = *s1++;
	while (*s2 != '\0')
		*wp++ = *s2++;
	*wp = '\0';
	free(tofree);
	return (res);
}

static int	free_and_error(char **load_file, char **line)
{
	if (load_file != NULL && *load_file != NULL)
	{
		free(*load_file);
		*load_file = NULL;
	}
	if (line != NULL)
		*line = NULL;
	return (-1);
}

static int	next_from_str(char **load_file, char **line)
{
	char	*tail_str;

	tail_str = ft_strchr(*load_file, '\n');
	*tail_str++ = '\0';
	*line = *load_file;
	if ((*load_file = ft_strdup(tail_str)) == NULL)
		return (-1);
	return (1);
}

static int	read_from_tail(char **load_file, char **line, ssize_t byte_read)
{
	if (byte_read < 0)
		return (free_and_error(load_file, line));
	if (*load_file != NULL && ft_strchr(*load_file, '\n') != NULL)
		return (next_from_str(load_file, line));
	if (*load_file != NULL)
	{
		*line = *load_file;
		*load_file = NULL;
		return (0);
	}
	if ((*line = ft_strdup("")) == NULL)
		return (free_and_error(load_file, line));
	return (0);
}

/*
** Parameters:
** #1. file descriptor for reading
** #2. The value of what has been read
** Return value:
** 1 : A line has been read
** 0 : EOF has been reached
** -1 : An error happened
*/

int			get_next_line(int fd, char **line)
{
	static char	*list_fd[ULIMITN];
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		byte_read;

	if (fd < 0 || line == NULL)
		return (-1);
	if (read(fd, buffer, 0) < 0)
		return (free_and_error(list_fd + fd, line));
	if (list_fd[fd] != NULL && ft_strchr(list_fd[fd], '\n') != NULL)
		return (next_from_str(list_fd + fd, line));
	if (*(list_fd + fd) == 0)
		*(list_fd + fd) = ft_strdup("");
	while ((byte_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[byte_read] = '\0';
		if ((list_fd[fd] = ft_strjoin_free(list_fd[fd], buffer)) == NULL)
			return (free_and_error(list_fd + fd, line));
		if (ft_strchr(list_fd[fd], '\n') != NULL)
			return (next_from_str(list_fd + fd, line));
	}
	if (byte_read == 0 && *(list_fd + fd)[0] == '\0')
		return ('E');
	return (read_from_tail(list_fd + fd, line, byte_read));
}
