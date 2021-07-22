/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:20:48 by wnormcor          #+#    #+#             */
/*   Updated: 2021/02/01 16:48:51 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** tokenizer.c
*/

void		ms_tokenizer_free(t_tok **pp_tok)
{
	t_tok	*dell;
	t_tok	*plst;

	if (pp_tok)
	{
		plst = *pp_tok;
		while (plst)
		{
			dell = plst;
			plst = plst->next;
			free(dell->data);
			dell->data = NULL;
			free(dell);
			dell = NULL;
		}
		*pp_tok = NULL;
	}
}

/*
** parser.c
*/

void		ms_parser_free(t_cmd **cmd)
{
	if ((*cmd))
	{
		ft_free_tmp((*cmd)->cmd_name);
		ft_free_tmp((*cmd)->cmd_dir);
		ft_lstclear(&(*cmd)->lst, ft_lstdelone_f);
		ms_parser_free(&((*cmd)->redir));
		ms_parser_free(&((*cmd)->pipe));
		ms_parser_free(&((*cmd)->next));
		free((*cmd));
		(*cmd) = NULL;
	}
}

static void	freeing_memory_from_struct_env(t_env *data)
{
	ft_free_two_dimensional_arr(data->envp);
	free(data);
	data = NULL;
}

void		ms_exit(t_cmd *cmd, t_env *p_env, int num)
{
	if (cmd)
		ms_parser_free(&cmd);
	if (p_env)
		freeing_memory_from_struct_env(p_env);
	exit(num);
}

void		ms_err_and_exit(t_cmd *cmd, t_env *data, char *str)
{
	ft_putendl_fd(str, 2);
	ms_exit(cmd, data, 1);
}
