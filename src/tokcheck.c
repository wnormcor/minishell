/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokcheck.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 09:51:50 by wnormcor          #+#    #+#             */
/*   Updated: 2021/02/01 22:47:47 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	tokcheck_db(t_tok *next)
{
	if (next->next)
	{
		if (*next->next->data == *next->data)
			return (1);
	}
	return (0);
}

static	int	print_error(char *err, char *sym)
{
	ft_putstr(err);
	ft_putstr(sym);
	g_exit_status = 2;
	return (1);
}

static int	tokchek_one(t_tok *t)
{
	if (*t->data == ';' && (*t->next->data == ';' || *t->next->data != ';'))
		return (print_error(ERR, tokcheck_db(t->next) ? "`;;'\n" : "`;'\n"));
	if (*t->data == '>' && (!*t->next->data || (*t->next->data == '>' &&
		!*t->next->next->data)))
		return (print_error(ERR, "`newline'\n"));
	if (*t->data == '>' && ((*t->next->data == '>' || *t->next->data == ';')
		&& (*t->next->next->data == ';' || !*t->next->next->data)))
		return (print_error(ERR, "`;'\n"));
	if (*t->data == '>' && ((*t->next->data == '>' || *t->next->data == '|')
		&& (*t->next->next->data == '|' || !*t->next->next->data)))
		return (print_error(ERR, "`|'\n"));
	if (*t->data == '>' && ((t->next->data[0] == '\'' ||
		t->next->data[0] == '\"') && (t->next->data[1] == '\''
		|| t->next->data[1] == '\"')) && !t->next->next)
		return (print_error("minishell: : No such file or directory\n", NULL));
	if (*t->data == '>' && ((t->next->data[0] == '\'' ||
		t->next->data[0] == '\"') && !t->next->next))
		return (print_error("minishell: : No such file or directory\n", NULL));
	if (*t->data == '|' && t->next->data)
		return (print_error(ERR, "`|'\n"));
	if (*t->data == '>' && *t->next->data == ';' && t->next->next->data)
		return (print_error(ERR, "`|'\n"));
	return (0);
}

static int	tokcheck_more_one(t_tok *tok)
{
	char	*e;

	if (*tok->data == ';' && *tok->next->data == ';')
	{
		return (print_error(ERR, e = tokcheck_db(tok->next)\
													? "`;;'\n" : "`;'\n"));
	}
	if (*tok->data == '>' && (!*tok->next->data || *tok->next->data == ';'))
		return (print_error(ERR, "`newline'\n"));
	if (*tok->data == '>' && *tok->next->data == '>' &&\
												*tok->next->next->data == '>')
	{
		return (print_error(ERR, tokcheck_db(tok->next)\
													? "`>>'\n" : "`>'\n"));
	}
	return (0);
}

int			ms_tokcheck(t_tok *p_tok)
{
	t_tok	*tok;
	int		i;

	i = 0;
	tok = p_tok;
	if (*tok->data == '.' && (!tok->next || tok->next))
		return (print_error(ERR_FA, NULL));
	while (tok && ++i)
	{
		if (tok->next)
		{
			if (i == 1)
			{
				if (tokchek_one(tok))
					return (1);
			}
			else if (tokcheck_more_one(tok))
				return (1);
		}
		tok = tok->next;
	}
	return (0);
}
