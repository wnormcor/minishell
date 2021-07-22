/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 22:09:31 by wnormcor          #+#    #+#             */
/*   Updated: 2021/02/01 23:08:25 by wnormcor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** External functs from subject:
**
** <stdlib.h>		malloc, free, exit (+ EXIT_SUCCESS, EXIT_FAILURE)
** <unistd.h>		write, open, read, close,
**					fork, getcwd, chdir, execve, dup, dup2, pipe (+pid_t)
** <sys/wait.h>		wait, waitpid, wait3, wait4
** <signal.h>		signal, kill
** <sys/stat.h>		stat, lstat, fstat
** <dirent.h>		opendir, readdir, closedir
** <string.h>		strerror
** <sys/errno.h>	errno
*/

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"

# define MALLOCERR "Error : Malloc fail"
# define ERR "minishell: syntax error near unexpected token "
# define ERR_FA "filename argument required\n .: usage: . filename [argument]\n"

extern int				g_exit_status;

/*
**  structute for env.c
*/

typedef struct			s_env
{
	int					fd_0;
	int					fd_1;
	char				**envp;
	int					home_dir;
	int					current_pwd;
	int					old_pwd;
	int					env_var;
	int					path;
	int					count_str;
}						t_env;

t_env					*ms_env_create(char **envp);

/*
**  tokenizer.c & tokcheck.c
*/

enum {
	ST_GEN = 0,
	ST_DQT = 1,
	ST_QUT = 2,
	ST_DOL = 3,
};

typedef	struct			s_ctrl
{
	char				*str;
	int					str_len;
	struct s_tok		*first_elem;
	int					i;
	int					j;
	int					status;
	int					symbol;
}						t_ctrl;

typedef	struct			s_tok
{
	int					type;
	char				*data;
	struct s_tok		*next;
}						t_tok;

t_tok					*ms_tokenizer_make(char *str);
void					ms_tokenizer_free(t_tok **pp_tok);
int						ms_tokcheck(t_tok *p_tok);

/*
**  parser (and structure for parser & executor)
*/

typedef struct			s_cmd
{
	struct s_cmd		*parent;
	int					cmd_type;
	char				*cmd_dir;
	char				*cmd_name;
	int					cmd_argc;
	struct s_list		*lst;
	int					redir_type;
	struct s_cmd		*redir;
	struct s_cmd		*pipe;
	struct s_cmd		*next;
}						t_cmd;

typedef	enum			e_cmd_type
{
	CMD_ECHO = 0,
	CMD_CD = 1,
	CMD_PWD = 2,
	CMD_EXPORT = 3,
	CMD_UNSET = 4,
	CMD_ENV = 5,
	CMD_EXIT = 6,
	CMD_ERROR = 7,
	CMD_IN_PATH = 8,
}						t_cmd_type;

t_cmd					*ms_parser_make(t_env *p_env, t_tok *p_tok);
void					parser_add_lst(t_cmd **c, t_env *e, char **st, int t);
int						parser_checking_cmd(t_cmd *cmd, char *path);
void					ms_parser_free(t_cmd **pp_cmd);

/*
**  executor в syntax_tree
*/

void					ms_executor(t_cmd *p_cmd, t_env *p_env);
void					executor_fdclose(t_cmd *c, t_env *e, int fd0, int fd1);
void					executor_execve(t_cmd **pp_cmd, t_env **pp_env);

/*
** buildin commands
*/

void					bi_pwd(t_cmd *p_cmd, t_env *p_env);
void					bi_env(t_cmd *p_cmd, t_env *p_env);
void					bi_cd(t_cmd **pp_cmd, t_env *p_env);
void					bi_echo(t_cmd *p_cmd);

void					bi_export(t_cmd **pp_cmd, t_env **pp_env);
void					ex_check_args(t_cmd **pp_cmd);
void					ex_add_args(char **tenv, t_env **env, t_cmd **cmd);
int						ex_delete_lst(t_cmd **pp_cmd, t_list **pp_list,
										int num, int err);
void					ex_empty(t_env **pp_env, t_cmd **pp_cmd);

void					bi_unset(t_cmd **pp_cmd, t_env **pp_env);
int						un_del_lst(t_cmd **cmd, t_list **lst, int clt, int e);
void					un_del_env_var(t_env **p_env, t_cmd **pp_cmd);

void					bi_exit(t_cmd *p_cmd, t_env *p_env);

/*
** common utils for all modules
*/

void					ms_err_and_exit(t_cmd *p_cmd, t_env *p_env, char *str);
void					ms_put_error(char *s1, char *s2, char *s3, int num);
void					ms_exit(t_cmd *p_cmd, t_env *p_env, int exit_status);

/*
** promt & signal handlers
*/

enum {
	SIGMODE_PROMT,
	SIGMODE_WAIT,
	SIGMODE_DEF,
};

void					ms_promt();
void					ms_setup_signals(int sig_mode);

/*
** function for debuger
*/

void					db_print_tok_chain(t_tok *p_tok);

#endif
