/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 12:48:11 by wnormcor          #+#    #+#             */
/*   Updated: 2021/02/01 16:49:25 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_token(t_tok **pp_tok, t_ctrl *p_ctrl)
{
	(*pp_tok)->next = ft_calloc(sizeof(t_tok), 1);
	*pp_tok = (*pp_tok)->next;
	(*pp_tok)->data = ft_calloc(p_ctrl->str_len, 1);
	p_ctrl->j = 0;
}

static int	status_executor_3(t_tok **token, t_ctrl *p_ctrl)
{
	if (p_ctrl->status == ST_DQT || p_ctrl->status == ST_QUT)
	{
		if ((p_ctrl->symbol == '\"' && p_ctrl->status == ST_DQT) ||
			(p_ctrl->symbol == '\'' && p_ctrl->status == ST_QUT))
			p_ctrl->status = ST_GEN;
		(*token)->data[p_ctrl->j] = p_ctrl->str[p_ctrl->i];
		p_ctrl->j++;
	}
	else if (p_ctrl->status == ST_DOL)
	{
		if (p_ctrl->symbol == ';' || p_ctrl->symbol == '>' ||
			p_ctrl->symbol == '<' || p_ctrl->symbol == '|' ||
			p_ctrl->symbol == ' ')
		{
			p_ctrl->status = ST_GEN;
			p_ctrl->i--;
		}
		else
		{
			(*token)->data[p_ctrl->j] = p_ctrl->str[p_ctrl->i];
			p_ctrl->j++;
		}
	}
	return (0);
}

static int	status_executor_2(t_tok **token, t_ctrl *p_ctrl)
{
	if (p_ctrl->status == ST_GEN)
	{
		if (p_ctrl->symbol == '\"')
		{
			p_ctrl->status = ST_DQT;
			(*token)->type = '\"';
			(*token)->data[p_ctrl->j] = '\"';
			return (p_ctrl->j++);
		}
		else if (p_ctrl->symbol == '\'')
		{
			p_ctrl->status = ST_QUT;
			(*token)->type = '\'';
			(*token)->data[p_ctrl->j] = '\'';
			return (p_ctrl->j++);
		}
		else if (p_ctrl->symbol == '$')
		{
			p_ctrl->status = ST_DOL;
			(*token)->type = '$';
			(*token)->data[p_ctrl->j] = '$';
			return (p_ctrl->j++);
		}
	}
	return (status_executor_3(token, p_ctrl));
}

static void	status_executor(t_tok **token, t_ctrl *p_ctrl)
{
	if (p_ctrl->status == ST_GEN)
	{
		if (p_ctrl->symbol == -1)
		{
			(*token)->type = -1;
			(*token)->data[p_ctrl->j] = p_ctrl->str[p_ctrl->i];
			p_ctrl->j++;
		}
		else if (p_ctrl->symbol == ' ')
		{
			if (p_ctrl->j > 0)
				add_token(token, p_ctrl);
		}
		else if (p_ctrl->symbol == ';' || p_ctrl->symbol == '>' ||
				p_ctrl->symbol == '<' || p_ctrl->symbol == '|')
		{
			if (p_ctrl->j > 0)
				add_token(token, p_ctrl);
			(*token)->type = p_ctrl->str[p_ctrl->i];
			(*token)->data[0] = p_ctrl->str[p_ctrl->i];
			add_token(token, p_ctrl);
		}
	}
	status_executor_2(token, p_ctrl);
}

t_tok		*ms_tokenizer_make(char *input)
{
	t_ctrl	*p_ctrl;
	t_tok	*p_tok;

	p_ctrl = ft_calloc(sizeof(t_ctrl), 1);
	p_ctrl->str = input;
	p_ctrl->str_len = ft_strlen(p_ctrl->str);
	p_tok = ft_calloc(sizeof(t_tok), 1);
	p_tok->data = ft_calloc(p_ctrl->str_len + 1, 1);
	p_ctrl->first_elem = p_tok;
	while (p_ctrl->str[p_ctrl->i])
	{
		if (ft_strchr(" ;\'\"<>|$", p_ctrl->str[p_ctrl->i]))
			p_ctrl->symbol = *ft_strchr(" ;\'\"<>|$", p_ctrl->str[p_ctrl->i]);
		else
			p_ctrl->symbol = -1;
		status_executor(&p_tok, p_ctrl);
		p_ctrl->i++;
	}
	p_tok = p_ctrl->first_elem;
	free(p_ctrl);
	return (p_tok);
}
