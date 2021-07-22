/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 18:41:18 by wnormcor          #+#    #+#             */
/*   Updated: 2021/02/01 22:24:17 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	par_dollaradd(char **content, char option, char *p, int *i)
{
	if (option == 'a')
	{
		ft_free_tmp(*content);
		*content = ft_strdup("");
	}
	else
		*i = (p[(*i)] == '_' || ft_isalpha(p[(*i)])) ? 1 : 0;
}

static int	par_checkenv(char **envp, char *var, int size)
{
	int		i;
	int		j;
	int		amount;

	amount = size;
	i = -1;
	while (envp[++i])
	{
		j = 0;
		if (envp[i][j] == var[j])
		{
			size = amount;
			while (envp[i][j] == var[j] && size)
			{
				if ((envp[i][j + 1] == '=' || envp[i][j + 1] == '\0') &&\
																size == 1)
					return (i);
				j++;
				size--;
			}
		}
	}
	return (0);
}

static void	par_replacedollar(t_env *data, char **c, char **rem, int i)
{
	char		*p;
	int			num_env;
	char		*p_rem;

	p = *rem ? ft_strchr(*rem, '$') : ft_strchr(*c, '$');
	if (p)
	{
		par_dollaradd(c, 'b', ++p, &i);
		if (i)
		{
			while (p[i] == '_' || ft_isalnum(p[i]))
				i++;
			if ((num_env = par_checkenv(data->envp, p--, i)))
			{
				*p = '\0';
				p_rem = *rem;
				*rem = ft_strdup(p + i + 1);
				free(p_rem);
				*c = ft_strjoin_gnl(c, data->envp[num_env] + i + 1);
				**rem != '\0' ? par_replacedollar(data, c, rem, 0) : NULL;
			}
			else
				par_dollaradd(c, 'a', ++p, &i);
		}
	}
}

static void	par_stripquotes(char *content, size_t n, int j)
{
	size_t	i;
	char	end_quote;
	char	c;

	i = -1;
	end_quote = 0;
	while (++i < n)
	{
		c = content[i];
		if ((c == '\'' || c == '\"') && end_quote == 0)
			end_quote = c;
		else if (c == end_quote)
			end_quote = 0;
		else
			content[j++] = c;
	}
	content[j] = 0;
}

void		parser_add_lst(t_cmd **syntax_tree, t_env *data,
								char **content, int type)
{
	char *rem;

	rem = NULL;
	if (type == '\"')
	{
		par_replacedollar(data, content, &rem, 0);
		if (rem != NULL)
		{
			*content = ft_strjoin_gnl(content, rem);
			ft_free_tmp(rem);
		}
	}
	par_stripquotes(*content, ft_strlen(*content), 0);
	if (type == '$')
	{
		par_replacedollar(data, content, &rem, 0);
		if (rem != NULL)
		{
			*content = ft_strjoin_gnl(content, rem);
			ft_free_tmp(rem);
		}
	}
	if (*content && **content != '\0')
		ft_lstadd_back(&(*syntax_tree)->lst, ft_lstnew(ft_strdup(*content)));
}
