/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:05:20 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/24 11:04:33 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <limits.h>
# include <dirent.h>
# include "../libs/readline/readline.h"
# include "../libs/readline/history.h"
# include "../libs/libft/libft.h"
# include "../libs/ft_printf/ft_printf.h"
# include "defines.h"

/*parser and tokenization*/
int		manage_input(char *line, t_proc **lst_proc, t_exec *exec);
int		parsing_input(char *line, int *exit);
int		create_tokens(t_tok **lst_tok, char *input, t_exec *exec);
int		new_tok(t_tok **lst_tok, char *str, int type, int *exit);
int		ft_lstsize_tok(t_tok *lst);
t_tok	*ft_lstlast_tok(t_tok *lst);
void	ft_print_list_tok(t_tok **lst_tok);
void	free_lst_tok(t_tok **lst_tok);

/*expansion*/
int		remove_dol_end(t_tok **lst_tok, int *exit);
char 	*expander(t_tok **lst_tok, char *str, t_exec *exec, int type);
char	*find_dollar_sign(char *str, t_exec *exec, int *flag_exp);
char	*expand_error(char *str, int *i, t_exec *exec);
char	*check_expand(char *str, int *i, t_exec *exec, int *flag_exp);
int		split_tok(t_tok **lst_tok, char *str, int *exit);

/*process list*/
int		create_process(t_proc **lst_proc, t_tok **lst_tok, int *err);
int		create_str(t_proc *lst_proc, t_tok **lst_tok, int n_str, int *exit);
t_proc	*ft_lstnew_proc(void);
t_proc	*ft_lstlast_proc(t_proc *lst);
void	ft_lstadd_back_proc(t_proc **lst, t_proc *new);
void	sep_process(t_proc **lst_proc, t_tok **lst_tok);
char	*join_str_toks(t_tok **lst_tok);
int		find_outfile(t_proc *lst_proc, t_tok **lst_tok, int *err);
int		find_infile(t_proc *lst_proc, t_tok **lst_tok, int *err);
int		find_heredoc(t_proc *lst_proc, t_tok **lst_tok, int n_hd, int *err);
void	ft_print_process(t_proc **lst_proc);
void	free_lst_proc(t_proc **lst_proc);

/*lexer error managment*/
int		err_msg_parser(char *msg, int type, int ch, int *exit);
void	update_error(t_exec *exec);
void	init_error(t_exec *exec);

/*signals*/
void    init_signals(int mode);

/*heredoc*/
int	manage_heredoc(t_proc **lst_proc, t_exec *exec);

/*exec and process functions*/
int		exec_machine(t_proc *pcs_chain, t_exec *exec);
void	pipefd_calibrate(t_exec *exec);
void	launch_process(t_exec *exec, t_proc **pcs_chain);
void	command_process(t_proc *pcs_chain, t_exec *exec);
void	launch_process(t_exec *exec, t_proc **pcs_chain);
void	wait_processes(t_exec *exec);
char	*exec_path(char **all_path, t_proc *exec_trgt);
void	build_execve(t_proc **exec_trgt, t_exec **exec);
void	exec_bash(t_proc **exec_trgt, t_exec **exec);
char	**search_path(char *env[]);
void	relative_path_clean(t_proc **proc,  t_exec **exec);

/*utils for process and env*/
void	init_exec(t_exec *exec, char **env);
int		measure_list(t_proc **lst);
void	io_redirect(t_proc *pcs, t_exec *exec);
void	back_up_stdio(t_exec *exec, int io);
void	close_all_pipes(t_exec *exec);
void	free_exec(t_exec **exec);
int		error_msg(char *msg, int nb, t_exec *exec, t_proc *pcs);
int		error_fd_msg(char *msg, t_exec *exec, t_proc *pcs, char *fname);
int		fd_is_open(int fd);
void	free_split(char ***split_result);
char	**key_val_pair(char *str);
void	free_key_val(char **kvp);
void	free_pntr(void *pntr);
int		export_exec(t_exec *exec, char *arg, int type);
int		shlvl_add(t_exec *exec, int idx, char *tmp);

/*buil-tins prototypes*/
void	builtins(char **arg, t_exec *exec);
int		ft_pwd(t_exec *exec, char **arg);
int		ft_cd(t_exec *exec, char **arg);
int		ft_echo(t_exec *exec, char **arg);
int		ft_env(t_exec *exec, char **arg);
int		ft_export(t_exec *exec, char **arg);
int		ft_unset(t_exec *exec, char **arg);
int		is_builtin(t_proc*pcs_chain);
int		ft_exit(t_exec *exec, char **arg);
int		exec_builtin(t_proc *pcs_chain, t_exec *exec);
int		error_builtin(char *msg, int nb, char *bltn);

/* environment setup and modification*/
char	**env_dup(char **env, int i, int j);
int		count_var_env(char **env);
void	free_env(char	**env);
char	*extract_variable(char *key_value);
int		search_env_var(char **env, char *var);
char	**realloc_env(char **env, char *var);
char	**downsize_env(char **env, int idx, int i, int j);
char    *ft_getenv(char **env, char *target);
void	replace_env_var(char **env, char *target, char *replace);
char	*extract_value(char *key_value);
char	*build_env_var(char *arg, t_exec *exec, int type, int idx);
void	free_xpenv(t_xpenv	**list);
t_xpenv	*create_xp_env(char **env);
void	add_expenv(t_xpenv **xpenv, char *env, int type);


/* exec total malloc : pids, pipes, valid_path,   */

#endif
