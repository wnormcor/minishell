/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_execve.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:18:30 by wnormcor          #+#    #+#             */
/*   Updated: 2021/02/01 20:32:28 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <string.h>

static char	**executor_make_argv(t_cmd *cmd)
{
	char		**argv_for_execve;
	int			i;
	t_list		*tmp;

	i = 0;
	tmp = cmd->lst;
	argv_for_execve = (char **)malloc(sizeof(char *) * (cmd->cmd_argc + 2));
	argv_for_execve[i] = ft_strdup(cmd->cmd_name);
	i++;
	while (tmp)
	{
		argv_for_execve[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	argv_for_execve[i] = NULL;
	return (argv_for_execve);
}

void		executor_execve(t_cmd **cmd, t_env **data)
{
	int		status;
	char	*command;
	char	**argv_list_execve;
	int		fork_res;

	if ((fork_res = fork()) > 0)
	{
		ms_setup_signals(SIGMODE_WAIT);
		if (wait(&status) == -1)
			ms_err_and_exit(*cmd, *data, strerror(errno));
		g_exit_status = WEXITSTATUS(status);
	}
	else if (fork_res < 0)
	{
		ft_putendl("error with fork");
	}
	else
	{
		ms_setup_signals(SIGMODE_DEF);
		argv_list_execve = executor_make_argv(*cmd);
		command = ft_strjoin((*cmd)->cmd_dir, (*cmd)->cmd_name);
		execve(command, argv_list_execve, (*data)->envp);
		exit(EXIT_FAILURE);
	}
}
