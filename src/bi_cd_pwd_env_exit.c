/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd_pwd_env_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 13:38:48 by wnormcor          #+#    #+#             */
/*   Updated: 2021/02/01 12:07:33 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <string.h>

static void	bi_cd_2(t_cmd *cmd, t_env **all)
{
	char	*tmp;
	char	*tmp_2;
	char	*tmp_3;

	tmp = (*all)->envp[(*all)->old_pwd];
	if (!((*all)->envp[(*all)->old_pwd] = ft_strjoin("OLD", \
			(*all)->envp[(*all)->current_pwd])))
		ms_err_and_exit(cmd, *all, "Error : Malloc fail");
	free(tmp);
	if (!(tmp_2 = (char *)malloc(sizeof(char) * 100)))
		ms_err_and_exit(cmd, *all, "Error : Malloc fail");
	getcwd(tmp_2, 100);
	tmp = (*all)->envp[(*all)->current_pwd];
	tmp_3 = ft_strndup(tmp_2, ft_strlen(tmp_2));
	free(tmp_2);
	if (!((*all)->envp[(*all)->current_pwd] = ft_strjoin("PWD=", \
			tmp_3)))
		ms_err_and_exit(cmd, *all, "Error : Malloc fail");
	free(tmp);
	free(tmp_3);
}

void		bi_cd(t_cmd **cmd, t_env *all)
{
	char	*tmp_path;

	if ((*cmd)->cmd_argc == 0)
	{
		if (!((*cmd)->lst = (t_list *)malloc(sizeof(t_list))))
			ms_err_and_exit(*cmd, all, "Error : Malloc fail");
		((*cmd)->lst->content) = all->envp[all->home_dir] + 5;
		(*cmd)->lst->next = NULL;
	}
	if (((char*)(*cmd)->lst->content)[0] == '~')
	{
		if (!(tmp_path = ft_strjoin(all->envp[all->home_dir] + 5,
								(char *)(*cmd)->lst->content + 1)))
			ms_err_and_exit(*cmd, all, "Error : Malloc fail");
		free((char *)((*cmd)->lst->content));
		((*cmd)->lst->content) = tmp_path;
	}
	if (chdir((char *)(*cmd)->lst->content) != 0)
	{
		ms_put_error("minishell: cd: ", (*cmd)->lst->content, \
						": No such file or directory", 0);
		g_exit_status = 1;
	}
	bi_cd_2(*cmd, &all);
}

void		bi_pwd(t_cmd *p_cmd, t_env *p_env)
{
	int		status;

	if (fork())
	{
		ms_setup_signals(SIGMODE_WAIT);
		if (wait(&status) == -1)
			ms_err_and_exit(p_cmd, p_env, strerror(errno));
		g_exit_status = WEXITSTATUS(status);
	}
	else
	{
		ms_setup_signals(SIGMODE_DEF);
		if (!(p_env->envp[p_env->current_pwd]))
			ms_err_and_exit(p_cmd, p_env,
				"Error : too many characters in the path");
		ft_putendl(p_env->envp[p_env->current_pwd] + 4);
		exit(EXIT_SUCCESS);
	}
}

void		bi_env(t_cmd *cmd, t_env *p_env)
{
	int		status;

	if (fork())
	{
		ms_setup_signals(SIGMODE_WAIT);
		if (wait(&status) == -1)
			ms_err_and_exit(cmd, p_env, strerror(errno));
		g_exit_status = WEXITSTATUS(status);
	}
	else
	{
		ms_setup_signals(SIGMODE_DEF);
		status = -1;
		if (cmd->cmd_argc > 0)
		{
			ms_put_error("env: ", cmd->lst->content,
						": No such file or directory", 0);
			exit(127);
		}
		else
			while (p_env->envp[++status])
				ft_putendl(p_env->envp[status]);
		exit(EXIT_SUCCESS);
	}
}

void		bi_exit(t_cmd *cmd, t_env *p_env)
{
	int		number;

	ft_putendl("exit");
	if (cmd->cmd_argc == 0)
		ms_exit(cmd, p_env, g_exit_status);
	else if (cmd->cmd_argc > 0)
	{
		number = ft_atoi(cmd->lst->content);
		if (!number || ((int)ft_strlen(ft_itoa(number)) <
			(int)ft_strlen(cmd->lst->content)))
		{
			ms_put_error("minishell: exit: ", cmd->lst->content,
						": numeric argument required", 0);
			g_exit_status = 255;
			ms_exit(cmd, p_env, g_exit_status);
		}
		else if (cmd->cmd_argc == 1)
		{
			g_exit_status = (number > 255) ? (number - 256) : number;
			ms_exit(cmd, p_env, g_exit_status);
		}
		else if (cmd->cmd_argc > 1)
			ms_put_error("minishell: ", "exit: ", "too many arguments", 0);
		g_exit_status = 1;
	}
}
