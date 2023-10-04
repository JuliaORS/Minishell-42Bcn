/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:05:20 by julolle-          #+#    #+#             */
/*   Updated: 2023/09/27 16:41:17 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include "./libft/libft.h"

# define EBADF 9
# define ENOMEM 12
# define NOPERM 126
# define CMNOFOUND 127
# define STDIN	0

typedef struct s_proc {
	char			**arg;
	int				pos;
	int				fd[2];
	char			*infile;
	char			*outfile;
	int				intype;
	struct s_proc	*prev;
	struct s_proc	*next;
}	t_proc;

typedef struct s_tok {
	char			*str;
	int				type;
	struct s_tok	*prev;
	struct s_tok	*next;
}	t_tok;

typedef struct s_exec {
	char	**env;
	int		*pipes;
	pid_t	*pids;
	int		total_pcs;
	char	*path;  
}	t_exec;

int		minishell(int argc, char **argv);
t_tok	*ft_lstnew_tok(char *str, int type);
void	ft_lstadd_back_tok(t_tok **lst, t_tok *new);
t_proc	*ft_lstnew_proc();
t_proc	*ft_lstlast_proc(t_proc *lst);
void	ft_lstadd_back_proc(t_proc **lst, t_proc *new);
int		create_tokens(t_tok **lst_tok, char *line);
void	ft_print_list(t_tok *lst_tok);
void	ft_print_process(t_proc *lst_proc);
void	sep_process(t_proc **lst_proc, t_tok **lst_tok);
int		parsing_input(char *line, int *exit_status);
void	create_process(t_proc **lst_proc, t_tok **lst_tok);

/*exec and process functions*/
int		exec_machine(t_proc *pcs_chain, char *env[]);
void	pipefd_calibrate(t_exec *exec);
void	launch_process(t_exec *exec, t_proc **pcs_chain);
void	command_process(t_proc **pcs_chain, t_exec **exec, int pos);
void	launch_process(t_exec *exec, t_proc **pcs_chain);
void	wait_processes(t_exec *exec);
char	*exec_path(char **all_path, t_proc *exec_trgt);
void	build_execve(t_proc **exec_trgt, t_exec **exec);
void	exec_bash(t_proc **exec_trgt, t_exec **exec);
char	**search_path(char *env[]);
void	first_process(t_proc *exec_trgt, t_exec **exec);
void	last_process(t_proc *exec_trgt, t_exec **exec);
void	mid_process(t_proc *exec_trgt, t_exec **exec);

/*utils for process and env*/
void	init_exec(t_exec *exec, t_proc *pcs_chain, char **env);
int		measure_list(t_proc **lst);
void	redirect_input(int	input_fd);
void	redirect_output(int output_fd);
void	close_all_pipes(t_exec *exec);
void	free_chain(t_proc **pcs_chain);
void	free_arg(char **arg);
void	free_exec(t_exec **exec);
int		error_msg(char *msg, int nb, t_exec *exec, t_proc *pcs);


/*buil-tins and environtment prototypes*/
void	builtins(char **arg, t_exec *exec);
int		ft_pwd(t_exec *exec, char **arg);
int		ft_cd(t_exec *exec, char **arg);
int		ft_echo(t_exec *exec, char **arg);
int		ft_env(t_exec *exec, char **arg);
int		ft_export(t_exec *exec, char **arg);
int		ft_unset(t_exec *exec, char **arg);

/* environment setup and modification */
char	**env_dup(char **env);
int		count_var_env(char **env);
void	free_env(char	**env);
char	*extract_variable(char *key_value);
int		search_env_var(char **env, char *var);
char	**realloc_env(char **env, char *var);
char	**downsize_env(char **env, int idx, int i, int j);
char    *ft_getenv(char **env, char *target);
void	replace_env_var(char **env, char *target, char *replace);

#endif
