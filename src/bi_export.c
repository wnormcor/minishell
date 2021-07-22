/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:57:16 by wnormcor          #+#    #+#             */
/*   Updated: 2021/02/01 22:46:58 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ex_ret_char_pos(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (0);
	return (i);
}

static void	record_end_of_array(char ***pp_envp, int i, t_env **all)
{
	while ((*pp_envp)[++i])
		(*all)->envp[i] = (*pp_envp)[i];
	(*all)->envp[i] = NULL;
	free(*pp_envp);
}

static int	ex_change(t_env **all, t_list **p_cmd_lst, t_cmd **cmd,\
														int *list_amount)
{
	int		index;
	char	**pp_envp;
	int		i;

	index = -1;
	while ((*all)->envp[++index])
		if (ft_strncmp((char *)(*p_cmd_lst)->content, (*all)->envp[index],\
						ex_ret_char_pos((*all)->envp[index], '=') + 1) == 0)
		{
			pp_envp = (*all)->envp;
			if (!((*all)->envp = (char **)malloc(sizeof(char *) *\
											(*all)->count_str + 1)))
				ms_err_and_exit(*cmd, *all, MALLOCERR);
			i = -1;
			while (++i < index)
				(*all)->envp[i] = pp_envp[i];
			if (!((*all)->envp[i] = ft_strdup((char *)(*p_cmd_lst)->content)))
				ms_err_and_exit(*cmd, *all, MALLOCERR);
			free(pp_envp[i]);
			record_end_of_array(&pp_envp, i, all);
			ex_delete_lst(cmd, p_cmd_lst, *list_amount, 0);
			return (1);
		}
	return (0);
}

static void	ex_change_var(t_env **all, t_cmd **cmd, int list_amount)
{
	t_list	*p_cmd_lst;
	int		err;

	p_cmd_lst = (*cmd)->lst;
	while (p_cmd_lst)
	{
		err = ex_change(all, &p_cmd_lst, cmd, &list_amount);
		if (err == 0)
		{
			p_cmd_lst = p_cmd_lst->next;
			list_amount++;
		}
	}
}

void		bi_export(t_cmd **p_cmd, t_env **pp_env)
{
	char	**temp_env;
	int		index;

	index = -1;
	if ((*p_cmd)->lst)
	{
		ex_check_args(p_cmd);
		while (++index < (*p_cmd)->cmd_argc)
			ex_change_var(pp_env, p_cmd, 0);
		(*pp_env)->count_str += (*p_cmd)->cmd_argc;
		temp_env = (*pp_env)->envp;
		if (!((*pp_env)->envp = (char **)malloc(sizeof(char *) * \
								((*pp_env)->count_str + 1))))
			ms_err_and_exit(*p_cmd, *pp_env, MALLOCERR);
		ex_add_args(temp_env, pp_env, p_cmd);
		free(temp_env);
	}
	else
		ex_empty(pp_env, p_cmd);
}
