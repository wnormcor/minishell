/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 11:50:50 by wnormcor          #+#    #+#             */
/*   Updated: 2021/02/01 22:19:17 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

static char		*read_cmd(void)
{
	char	*line;
	int		ret;

	line = NULL;
	while (line == NULL)
	{
		ms_promt();
		ret = get_next_line(0, &line);
		if (ret == 'E')
		{
			ft_putendl("exit");
			exit(g_exit_status);
		}
		if (ret < 0)
			line = NULL;
		else if (ret >= 0 && *line == '\0')
		{
			free(line);
			line = NULL;
		}
	}
	return (line);
}

int				main(int argc, char **argv, char **envp)
{
	t_env			*p_env;
	char			*line;
	t_tok			*p_tok;
	t_cmd			*p_cmd;

	(void)argc;
	(void)argv;
	p_env = ms_env_create(envp);
	while (1)
	{
		ms_setup_signals(SIGMODE_PROMT);
		line = read_cmd();
		p_tok = ms_tokenizer_make(line);
		free(line);
		if (ms_tokcheck(p_tok) == 0)
		{
			p_cmd = ms_parser_make(p_env, p_tok);
			ms_executor(p_cmd, p_env);
			ms_parser_free(&p_cmd);
		}
		ms_tokenizer_free(&p_tok);
	}
	exit(EXIT_SUCCESS);
}
