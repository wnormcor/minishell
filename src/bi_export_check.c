/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 12:42:34 by wnormcor          #+#    #+#             */
/*   Updated: 2021/02/01 22:26:24 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ex_check_one_arg(t_list **p_cmd_lst, int *err, t_cmd **cmd,\
													int *list_amount)
{
	int		index;

	index = 0;
	while (((char*)(*p_cmd_lst)->content)[++index] != '=' && \
		((char*)(*p_cmd_lst)->content)[index] != '\0')
	{
		if (((char*)(*p_cmd_lst)->content)[index] != '_' && \
			ft_isalpha(((char*)(*p_cmd_lst)->content)[index]) != 1 \
			&& ft_isalnum(((char*)(*p_cmd_lst)->content)[index]) != 1)
		{
			*err = ex_delete_lst(cmd, p_cmd_lst, *list_amount, 1);
			return (1);
		}
	}
	if (*err == 0 && (*p_cmd_lst) && \
		((char*)(*p_cmd_lst)->content)[index] == '\0')
		*err = ex_delete_lst(cmd, p_cmd_lst, *list_amount, 0);
	return (0);
}

void		ex_check_args(t_cmd **cmd)
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
		{
			if (ex_check_one_arg(&p_cmd_lst, &err, cmd, &list_amount) == 1)
				break ;
		}
		else
			err = ex_delete_lst(cmd, &p_cmd_lst, list_amount, 1);
		if (err == 0)
		{
			p_cmd_lst = p_cmd_lst->next;
			list_amount++;
		}
	}
}
