/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 18:27:56 by wnormcor          #+#    #+#             */
/*   Updated: 2021/02/01 22:23:21 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

static int	par_check_dir_name(t_cmd *cmd, char *p_cmd_name, char *p)
{
	char	*pathname;

	if (!access(p_cmd_name, F_OK))
	{
		pathname = cmd->cmd_name;
		cmd->cmd_dir = ft_strndup(p_cmd_name, p - p_cmd_name);
		cmd->cmd_name = ft_strdup(p);
		free(pathname);
		pathname = NULL;
		return (0);
	}
	return (1);
}

static int	par_set_cmd_dir(t_cmd **cmd, char ***split_path, DIR **dir, int *i)
{
	int		j;
	char	*p_cmd_name;

	j = 0;
	p_cmd_name = (*cmd)->cmd_name;
	(*cmd)->cmd_name = ft_strjoin("/", (*cmd)->cmd_name);
	free(p_cmd_name);
	(*cmd)->cmd_dir = ft_strdup((*split_path)[(*i)]);
	while ((*split_path)[j])
		ft_free_tmp((*split_path)[j++]);
	free((*split_path));
	free((*dir)->__dd_buf);
	free(*dir);
	*dir = NULL;
	return (0);
}

static int	par_find_cmd_in_path(t_cmd *cmd, char *p_cmd_name,\
													char **split_path)
{
	DIR				*dir;
	struct dirent	*entry;
	int				i;
	char			*p;

	i = -1;
	if ((p = ft_strrchr(p_cmd_name, '/')))
	{
		ft_free_two_dimensional_arr(split_path);
		return (par_check_dir_name(cmd, p_cmd_name, ++p));
	}
	while (split_path[++i])
	{
		dir = opendir(split_path[i]);
		while ((entry = readdir(dir)))
			if (!ft_strcmp(entry->d_name, p_cmd_name))
				return (par_set_cmd_dir(&cmd, &split_path, &dir, &i));
		if (dir)
		{
			free(dir->__dd_buf);
			ft_free_tmp(dir);
		}
	}
	ft_free_two_dimensional_arr(split_path);
	return (1);
}

static int	par_set_cmd_type(t_cmd *cmd, char *p_cmd_name, char *path)
{
	if (!(ft_strcmp("echo", p_cmd_name)))
		return (CMD_ECHO);
	else if (!(ft_strcmp("cd", p_cmd_name)))
		return (CMD_CD);
	else if (!(ft_strcmp("pwd", p_cmd_name)))
		return (CMD_PWD);
	else if (!(ft_strcmp("export", p_cmd_name)))
		return (CMD_EXPORT);
	else if (!(ft_strcmp("unset", p_cmd_name)))
		return (CMD_UNSET);
	else if (!(ft_strcmp("env", p_cmd_name)))
		return (CMD_ENV);
	else if (!(ft_strcmp("exit", p_cmd_name)))
		return (CMD_EXIT);
	else if (path && !par_find_cmd_in_path(cmd,\
				p_cmd_name, ft_split(path + 5, ':')))
		return (CMD_IN_PATH);
	return (CMD_ERROR);
}

int			parser_checking_cmd(t_cmd *cmd, char *path)
{
	char		*p_cmd_name;
	size_t		i;

	i = -1;
	p_cmd_name = cmd->cmd_name;
	while (p_cmd_name[++i])
	{
		if (ft_isalpha(p_cmd_name[i]))
			if (p_cmd_name[i] >= 'A' && p_cmd_name[i] <= 'Z')
				p_cmd_name[i] += 32;
	}
	if (p_cmd_name[i])
		return (-1);
	return (par_set_cmd_type(cmd, p_cmd_name, path));
}
