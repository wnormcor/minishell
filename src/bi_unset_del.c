/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset_del.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:18:54 by wnormcor          #+#    #+#             */
/*   Updated: 2021/02/01 22:26:51 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	un_findchar(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != c)
		i++;
	return (i);
}

static void		un_del_arg(t_cmd **cmd, char **pp_env, int *k,\
																t_env **all)
{
	t_list	*p_cmd_lst;
	size_t	f;

	p_cmd_lst = (*cmd)->lst;
	while (p_cmd_lst && pp_env[*k])
	{
		f = un_findchar(pp_env[*k], '=');
		if (ft_strncmp((char *)p_cmd_lst->content, "PATH", f) == 0 && f == 4)
			(*all)->path = -1;
		if (ft_strncmp((char *)p_cmd_lst->content, pp_env[*k], f) == 0\
							&& f == ft_strlen((char *)p_cmd_lst->content))
		{
			*k += 1;
			free(pp_env[*k - 1]);
			p_cmd_lst = (*cmd)->lst;
		}
		else
			p_cmd_lst = p_cmd_lst->next;
	}
}

static void		un_del_next_lst(t_list **p_cmd_lst, int *err, int *list_amount,\
														t_list **lst_for_del)
{
	while ((*p_cmd_lst))
	{
		if (*err == *list_amount - 1)
		{
			(*p_cmd_lst)->next = (*lst_for_del)->next;
			(*lst_for_del) = (*p_cmd_lst)->next;
		}
		(*p_cmd_lst) = (*p_cmd_lst)->next;
		(*err)++;
	}
}

int				un_del_lst(t_cmd **cmd, t_list **lst_for_del, int list_amount,\
																	int err)
{
	t_list	*p_cmd_lst;
	t_list	*tmp_lst_del;

	if (err == 1)
		ms_put_error("minishell: unset: `", (*lst_for_del)->content, \
					"': not a valid identifier", 1);
	tmp_lst_del = (*lst_for_del);
	p_cmd_lst = (*cmd)->lst;
	err = 0;
	if (list_amount == 0)
	{
		(*lst_for_del) = p_cmd_lst->next;
		(*cmd)->lst = p_cmd_lst->next;
	}
	else
		un_del_next_lst(&p_cmd_lst, &err, &list_amount, lst_for_del);
	(*cmd)->cmd_argc--;
	free(tmp_lst_del);
	return (1);
}

void			un_del_env_var(t_env **all, t_cmd **cmd)
{
	char	**pp_env;
	int		k;
	int		i;

	k = 0;
	i = 0;
	(*all)->count_str -= (*cmd)->cmd_argc;
	pp_env = (*all)->envp;
	if (!((*all)->envp = (char **)malloc(sizeof(char *) * \
			((*all)->count_str + 1))))
		ms_err_and_exit(*cmd, *all, "Error : Malloc fail");
	while (pp_env[k])
	{
		un_del_arg(cmd, pp_env, &k, all);
		if (pp_env[k])
		{
			(*all)->envp[i] = pp_env[k];
			i++;
			k++;
		}
	}
	(*all)->envp[i] = NULL;
	free(pp_env);
}
