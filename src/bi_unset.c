/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 13:30:57 by wnormcor          #+#    #+#             */
/*   Updated: 2021/02/01 22:27:12 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		un_find_copy(t_env **all, t_list *p_cmd_lst)
{
	size_t	i;
	size_t	j;
	int		argc;

	i = 0;
	argc = 0;
	while ((*all)->envp[i])
	{
		j = 0;
		while ((*all)->envp[i][j] != '=')
			j++;
		if (ft_strncmp((char *)p_cmd_lst->content, (*all)->envp[i], j) == 0\
								&& j == ft_strlen((char *)p_cmd_lst->content))
			argc = 1;
		i++;
	}
	return (argc);
}

static void		un_del_unkn_envp(t_env **all, t_cmd **cmd)
{
	t_list	*p_cmd_lst;
	int		list_amount;
	int		arg;

	p_cmd_lst = (*cmd)->lst;
	list_amount = 0;
	while (p_cmd_lst)
	{
		arg = un_find_copy(all, p_cmd_lst);
		if (arg == 0)
			un_del_lst(cmd, &p_cmd_lst, list_amount, 0);
		else
		{
			p_cmd_lst = p_cmd_lst->next;
			list_amount++;
		}
	}
}

static int		un_check_args(t_list **p_cmd_lst, t_cmd **cmd, int *list_amount)
{
	int index;
	int	err;

	index = 1;
	err = 0;
	while (((char*)(*p_cmd_lst)->content)[index] != '\0')
	{
		if (((char*)(*p_cmd_lst)->content)[index] != '_' && \
			ft_isalpha(((char*)(*p_cmd_lst)->content)[index]) != 1 \
			&& ft_isalnum(((char*)(*p_cmd_lst)->content)[index]) != 1)
		{
			err = un_del_lst(cmd, p_cmd_lst, *list_amount, 1);
			break ;
		}
		index++;
	}
	return (err);
}

static void		un_check_unset(t_cmd **cmd)
{
	t_list	*p_cmd_lst;
	int		list_amount;
	int		err;

	p_cmd_lst = (*cmd)->lst;
	list_amount = 0;
	while (p_cmd_lst)
	{
		err = 0;
		if ((((char*)p_cmd_lst->content)[0]) == '_' || \
				ft_isalpha(((char*)p_cmd_lst->content)[0]) == 1)
			err = un_check_args(&p_cmd_lst, cmd, &list_amount);
		else
			err = un_del_lst(cmd, &p_cmd_lst, list_amount, 1);
		if (err == 0)
		{
			p_cmd_lst = p_cmd_lst->next;
			list_amount++;
		}
	}
}

void			bi_unset(t_cmd **cmd, t_env **all)
{
	un_check_unset(cmd);
	un_del_unkn_envp(all, cmd);
	if ((*cmd)->lst)
		un_del_env_var(all, cmd);
}
