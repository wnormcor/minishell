/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:40:22 by wnormcor          #+#    #+#             */
/*   Updated: 2021/02/01 21:21:07 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	executor_set_redir(t_cmd *p_cmd)
{
	int		fd;

	if (p_cmd)
		while (p_cmd->redir)
		{
			if (p_cmd->redir_type == '<')
			{
				if ((fd = open(p_cmd->redir->cmd_name, O_CREAT, 0644)) == -1)
					return (1);
			}
			else
			{
				if (p_cmd->redir_type == '>')
					fd = open(p_cmd->redir->cmd_name, O_CREAT |
								O_RDWR | O_TRUNC, S_IRWXU);
				if (p_cmd->redir_type == '^')
					fd = open(p_cmd->redir->cmd_name, O_CREAT |
								O_RDWR | O_APPEND, S_IRWXU);
			}
			dup2(fd, (p_cmd->redir_type == '<') ? 0 : 1);
			p_cmd = p_cmd->redir;
		}
	return (0);
}

static void	executor_run_cmd(t_cmd **cmd, t_env *data)
{
	if (executor_set_redir(*cmd))
		return ;
	if ((*cmd)->cmd_type == CMD_PWD)
		bi_pwd((*cmd), data);
	else if ((*cmd)->cmd_type == CMD_ENV)
		bi_env((*cmd), data);
	else if ((*cmd)->cmd_type == CMD_CD)
		bi_cd(cmd, data);
	else if ((*cmd)->cmd_type == CMD_ECHO)
		bi_echo(*cmd);
	else if ((*cmd)->cmd_type == CMD_EXPORT)
		bi_export(cmd, &data);
	else if ((*cmd)->cmd_type == CMD_UNSET)
		bi_unset(cmd, &data);
	else if ((*cmd)->cmd_type == CMD_IN_PATH)
		executor_execve(cmd, &data);
	else if ((*cmd)->cmd_type == CMD_EXIT)
		bi_exit(*cmd, data);
	else if ((*cmd)->cmd_type == CMD_ERROR && *((*cmd)->cmd_name) != '\0')
		ms_put_error("minishell: ",
			(*cmd)->cmd_name, ": command not found", 127);
	if ((*cmd)->redir)
		if ((*cmd)->redir->next)
			*cmd = (*cmd)->redir;
}

static void	executor_cmd_line(t_cmd **cmd, t_env *data)
{
	int			fd[2];
	t_cmd		*pip;

	fd[0] = 0;
	fd[1] = 0;
	if ((*cmd)->cmd_name || (*cmd)->redir_type)
	{
		pip = (*cmd);
		if (pip->pipe)
		{
			pipe(fd);
			dup2(fd[1], 1);
		}
		executor_run_cmd(cmd, data);
		executor_fdclose(pip, data, fd[0], fd[1]);
	}
}

void		executor_fdclose(t_cmd *pip, t_env *p_env, int fd0, int fd1)
{
	dup2(fd0, 0);
	if (fd1 != 0)
		close(fd1);
	if (fd0 != 0)
		close(fd0);
	if (pip->pipe)
	{
		close(1);
		dup2(p_env->fd_1, 1);
		executor_cmd_line(&pip->pipe, p_env);
	}
}

void		ms_executor(t_cmd *p_cmd, t_env *p_env)
{
	t_cmd	*next_cmd;

	next_cmd = p_cmd;
	while (next_cmd)
	{
		executor_cmd_line(&next_cmd, p_env);
		next_cmd = next_cmd->next;
		dup2(p_env->fd_1, 1);
		dup2(p_env->fd_0, 0);
	}
}
