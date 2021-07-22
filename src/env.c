/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 21:46:37 by wnormcor          #+#    #+#             */
/*   Updated: 2021/02/01 21:48:36 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		env_set_indexes(t_env *p_env)
{
	int	i;

	i = -1;
	while (p_env->envp[++i])
	{
		if (!ft_strncmp(p_env->envp[i], "PATH=", 5))
			p_env->path = i;
		else if (!ft_strncmp(p_env->envp[i], "HOME=", 5))
			p_env->home_dir = i;
		else if (!ft_strncmp(p_env->envp[i], "PWD=", 4))
			p_env->current_pwd = i;
		else if (!ft_strncmp(p_env->envp[i], "OLDPWD=", 7))
			p_env->old_pwd = i;
		else if (!ft_strncmp((p_env)->envp[i], "_=", 2))
			p_env->env_var = i;
	}
}

t_env			*ms_env_create(char **envp)
{
	t_env			*p_env;
	int				i;
	int				j;

	if (!(p_env = (t_env *)ft_calloc(sizeof(t_env), 1)))
		ms_err_and_exit(NULL, NULL, 0);
	p_env->fd_1 = dup(1);
	p_env->fd_0 = dup(0);
	i = 0;
	j = -1;
	while (envp[i])
		i++;
	if (!(p_env->envp = (char **)malloc(sizeof(char *) * (i + 1))))
		ms_err_and_exit(NULL, NULL, 0);
	while (++j != i)
		p_env->envp[j] = ft_strdup(envp[j]);
	p_env->envp[j] = NULL;
	p_env->count_str = i;
	env_set_indexes(p_env);
	return (p_env);
}
