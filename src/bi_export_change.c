/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export_change.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 12:37:53 by wnormcor          #+#    #+#             */
/*   Updated: 2021/02/01 22:26:18 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ex_delete_lst(t_cmd **cmd, t_list **lst, int amount_lst, int err)
{
	t_list	*p_cmd_lst;
	t_list	*tmp_lst;

	if (err == 1)
		ms_put_error("minishell: export: `", (*lst)->content,\
								"': not a valid identifier", 1);
	tmp_lst = (*lst);
	p_cmd_lst = (*cmd)->lst;
	err = -1;
	if (amount_lst == 0)
	{
		(*lst) = p_cmd_lst->next;
		(*cmd)->lst = p_cmd_lst->next;
	}
	else
	{
		while (p_cmd_lst && ++err != amount_lst - 1)
			p_cmd_lst = p_cmd_lst->next;
		p_cmd_lst->next = (*lst)->next;
		(*lst) = p_cmd_lst->next;
	}
	(*cmd)->cmd_argc--;
	free(tmp_lst->content);
	free(tmp_lst);
	return (1);
}

static void	ex_env_to_str(t_cmd *cmd, t_env *all, char **pp_envp)
{
	int		i;
	char	*str;
	char	*tmp_s;

	if (!(str = ft_strdup("")))
		ms_err_and_exit(cmd, all, "malloc: ft_env");
	i = 0;
	while (pp_envp[i])
	{
		tmp_s = str;
		if (!(str = ft_strjoin(str, "declare -x ")))
			ms_err_and_exit(cmd, all, "malloc: ft_env");
		free(tmp_s);
		tmp_s = str;
		if (!(str = ft_strjoin(str, pp_envp[i])))
			ms_err_and_exit(cmd, all, "malloc: ft_env");
		free(tmp_s);
		tmp_s = str;
		if (!(str = pp_envp[++i] ? ft_strjoin(str, "\n") : str))
			ms_err_and_exit(cmd, all, "malloc: ft_env");
		if (ft_strcmp(tmp_s, str) != 0)
			free(tmp_s);
	}
	ft_putendl(str);
	free(str);
}

static int	ex_create_array(char ***pp_envp, t_cmd **cmd, \
												t_env **all, char **tmp)
{
	int	index;
	int	i;
	int	flag;

	index = 0;
	i = 0;
	flag = 1;
	if (!((*pp_envp) = (char **)malloc(sizeof(char *) *\
					((*all)->count_str + 1))))
		ms_err_and_exit(*cmd, *all, "Error : Malloc fail");
	(*pp_envp)[i] = tmp[index];
	while (tmp[++index])
	{
		if (ft_strcmp((*pp_envp)[i], tmp[index]) > 0)
		{
			(*pp_envp)[i + 1] = (*pp_envp)[i];
			(*pp_envp)[i++] = tmp[index];
			flag = 0;
		}
		else
			(*pp_envp)[++i] = tmp[index];
	}
	(*pp_envp)[++i] = NULL;
	return (flag);
}

void		ex_empty(t_env **all, t_cmd **cmd)
{
	int		i;
	int		option;
	char	**tmp;
	char	**pp_envp;

	option = 0;
	i = -1;
	if (!(pp_envp = (char **)malloc(sizeof(char *) * ((*all)->count_str + 1))))
		ms_err_and_exit(*cmd, *all, "Error : Malloc fail");
	while ((*all)->envp[++i])
		pp_envp[i] = (*all)->envp[i];
	pp_envp[i] = NULL;
	while (option == 0)
	{
		tmp = pp_envp;
		option = ex_create_array(&pp_envp, cmd, all, tmp);
		free(tmp);
		tmp = NULL;
	}
	ex_env_to_str(*cmd, *all, pp_envp);
	free(pp_envp);
}

void		ex_add_args(char **temp_env, t_env **all, t_cmd **cmd)
{
	int		index;
	int		f;
	t_list	*p_cmd_lst;

	index = -1;
	while (temp_env[++index])
		(*all)->envp[index] = temp_env[index];
	p_cmd_lst = (*cmd)->lst;
	while (index < (*all)->count_str)
	{
		f = 0;
		while (p_cmd_lst->content[f] != '=')
			f++;
		if (ft_strncmp((char *)p_cmd_lst->content, "PATH", f) == 0 && f == 4)
			(*all)->path = index;
		(*all)->envp[index++] = ft_strdup(p_cmd_lst->content);
		p_cmd_lst = p_cmd_lst->next;
	}
	(*all)->envp[index] = NULL;
}
