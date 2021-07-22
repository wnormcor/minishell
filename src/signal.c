/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:59:47 by wnormcor          #+#    #+#             */
/*   Updated: 2021/02/01 16:48:30 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ms_promt(void)
{
	static int cmd_number = 1;

	ft_putstr_fd("\033[1;31m", 1);
	ft_putstr_fd("ms [", 1);
	ft_putnbr_fd(cmd_number, 1);
	ft_putstr_fd("]$ ", 1);
	ft_putstr_fd("\x1B[0m", 1);
	cmd_number++;
}

void		ms_put_error(char *str1, char *str2, char *str3, int exit_status)
{
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putendl_fd(str3, 2);
	if (exit_status)
		g_exit_status = exit_status;
}

static void	signal_for_promt(int sig_num)
{
	if (sig_num == SIGINT)
	{
		ft_putendl("\b\b  \b\b");
		g_exit_status = 1;
		ms_promt();
	}
	if (sig_num == SIGQUIT)
	{
		ft_putstr("\b\b  \b\b");
		g_exit_status = 0;
	}
}

static void	signal_for_wait(int sig_num)
{
	if (sig_num == SIGINT)
		ft_putstr("\n");
	else if (sig_num == SIGQUIT)
		ft_putstr("Quit: 3\n");
}

void		ms_setup_signals(int mode)
{
	if (mode == SIGMODE_PROMT)
	{
		signal(SIGINT, signal_for_promt);
		signal(SIGQUIT, signal_for_promt);
	}
	else if (mode == SIGMODE_WAIT)
	{
		signal(SIGINT, signal_for_wait);
		signal(SIGQUIT, signal_for_wait);
	}
	else if (mode == SIGMODE_DEF)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}
