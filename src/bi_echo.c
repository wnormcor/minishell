/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 13:38:35 by wnormcor          #+#    #+#             */
/*   Updated: 2021/02/01 22:26:08 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <string.h>

static char	*get_echo_str(t_cmd *cmd, t_list *first_list, int n_option)
{
	char	*final_line;
	char	*tmp;

	if (!(final_line = ft_strdup("")))
		ms_err_and_exit(cmd, NULL, "Error : Malloc fail");
	if (cmd->cmd_argc > 0)
		while (first_list)
		{
			tmp = final_line;
			if (!(final_line = ft_strjoin(final_line, first_list->content)))
				ms_err_and_exit(cmd, NULL, "Error : Malloc fail");
			free(tmp);
			tmp = final_line;
			if (!(final_line = first_list->next ?\
						ft_strjoin(final_line, " ") : final_line))
				ms_err_and_exit(cmd, NULL, "Error : Malloc fail");
			if (ft_strcmp(tmp, final_line) != 0)
				free(tmp);
			first_list = first_list->next;
		}
	if (n_option == 0)
		final_line = ft_strjoin_gnl(&final_line, "\n");
	return (final_line);
}

static void	print_echo(t_cmd *cmd)
{
	int		n_option;
	char	*output;
	t_list	*first_list;

	n_option = 0;
	first_list = cmd->lst;
	if (cmd->cmd_argc > 0)
	{
		if (ft_strcmp(cmd->lst->content, "-n") == 0)
		{
			n_option = 1;
			first_list = cmd->lst->next;
			cmd->cmd_argc--;
		}
		else if (!ft_strcmp(cmd->lst->content, "$?"))
		{
			ft_putnbr_fd(g_exit_status, 0);
			write(1, "\n", 1);
			exit(EXIT_SUCCESS);
		}
	}
	output = get_echo_str(cmd, first_list, n_option);
	ft_putstr(output);
	ft_free_tmp(output);
	exit(EXIT_SUCCESS);
}

void		bi_echo(t_cmd *p_cmd)
{
	int		status;

	if (fork())
	{
		ms_setup_signals(SIGMODE_WAIT);
		if (wait(&status) == -1)
			ms_err_and_exit(p_cmd, NULL, strerror(errno));
		g_exit_status = WEXITSTATUS(status);
	}
	else
	{
		ms_setup_signals(SIGMODE_DEF);
		print_echo(p_cmd);
	}
}
