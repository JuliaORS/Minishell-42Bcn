/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:05:20 by julolle-          #+#    #+#             */
/*   Updated: 2023/09/20 15:35:35 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <errno.h>
# include "./includes/libft/libft.h"

typedef struct s_proc {
	char			**arg;
	int				fd[2];
	int				position;
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

typedef struct s_env{
	char	*var;
	struct s_env *next;
}	t_env;

/*toakenisation process*/
int		minishell(int argc, char **argv);
t_tok	*ft_lstnew_tok(char *str, int type);
void	ft_lstadd_back_tok(t_tok **lst, t_tok *new);
int		create_tokens(t_tok **lst_tok, char *line);
void	ft_print_list(t_tok *lst_tok);

/* testing chain */
t_proc *create_chain(void);
t_proc *create_node(char **cmd, char *f_input, char *f_output, int position);

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

/*utils for process and env*/
void	init_exec(t_exec *exec, t_proc *pcs_chain, char **env);
int		measure_list(t_proc **lst);
void	redirect_input(int	input_fd);
void	redirect_output(int output_fd);
void	close_all_pipes(t_exec *exec);

/*buil-tins and environtment prototypes*/
void	builtins(char **arg, t_env *env);
void	ft_pwd(void);
void	ft_cd(char **arg);
void	ft_echo(char **arg);
t_env	*node_env(char *s);
t_env	*list_env(char **env);
void	free_listenv(t_env *list);
void	ft_env(t_env *env, char **arg);
void	ft_export(t_env **head, char **arg);

/* exec total malloc : pids, pipes, valid_path,   */
#endif
