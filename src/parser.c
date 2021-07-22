/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:06:42 by wnormcor          #+#    #+#             */
/*   Updated: 2021/02/01 22:24:30 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parser_init(t_cmd *cmd, t_env *data)
{
	t_list	*p_cmd_lst;

	if (!cmd->lst)
		return ;
	cmd->cmd_name = cmd->lst->content;
	if (data->path == -1)
		cmd->cmd_type = parser_checking_cmd(cmd, NULL);
	else
		cmd->cmd_type = parser_checking_cmd(cmd, data->envp[data->path]);
	p_cmd_lst = cmd->lst->next;
	free(cmd->lst);
	cmd->lst = p_cmd_lst;
	cmd->cmd_argc = ft_lstsize(cmd->lst);
}

static void	parser_pipe_semicolon(t_cmd **cmd, t_env *data, char c)
{
	if (c == 's')
	{
		parser_init(*cmd, data);
		(*cmd)->next = ft_calloc(sizeof(t_cmd), 1);
		(*cmd) = (*cmd)->next;
	}
	else
	{
		parser_init(*cmd, data);
		(*cmd)->pipe = ft_calloc(sizeof(t_cmd), 1);
		(*cmd) = (*cmd)->pipe;
	}
}

static void	parser_add_nodes(t_cmd **cmd, t_tok *p_tok, t_env *data)
{
	t_cmd	*p_cmd;

	p_cmd = (*cmd);
	if (p_tok->type == '>' || p_tok->type == '<')
	{
		parser_init(*cmd, data);
		(*cmd)->redir_type = p_tok->type;
		if ((*cmd)->parent && !(*cmd)->cmd_name)
		{
			if ((*cmd)->parent->redir_type == '>' &&\
										(*cmd)->redir_type == '>')
				(*cmd)->parent->redir_type = '^';
			(*cmd)->redir_type = 0;
			return ;
		}
		(*cmd)->redir = ft_calloc(sizeof(t_cmd), 1);
		(*cmd) = (*cmd)->redir;
		(*cmd)->parent = p_cmd;
	}
	else if (p_tok->type == ';')
		parser_pipe_semicolon(cmd, data, 's');
	else if (p_tok->type == '|')
		parser_pipe_semicolon(cmd, data, 'p');
	else
		parser_add_lst(cmd, data, &p_tok->data, p_tok->type);
}

t_cmd		*ms_parser_make(t_env *p_env, t_tok *p_tok)
{
	t_cmd	*p_cmd;
	t_cmd	*p_tcmd;

	p_cmd = NULL;
	p_cmd = ft_calloc(sizeof(t_cmd), 1);
	p_tcmd = p_cmd;
	while (p_tok)
	{
		parser_add_nodes(&p_tcmd, p_tok, p_env);
		p_tok = p_tok->next;
	}
	if (!p_cmd->next && !p_cmd->redir && !p_cmd->pipe)
		parser_init(p_cmd, p_env);
	if (!p_tcmd->next && !p_tcmd->redir && !p_tcmd->pipe && p_cmd != p_tcmd)
		parser_init(p_tcmd, p_env);
	return (p_cmd);
}
