/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:05:20 by julolle-          #+#    #+#             */
/*   Updated: 2023/09/28 14:48:56 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

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

/*toakenisation process*/
int		manage_input(char *line, t_proc **lst_proc, int *err);
int		create_tokens(t_tok **lst_tok, char *line, int *err);
t_tok	*ft_lstnew_tok(char *str, int type, int *err);
t_tok	*ft_lstlast_tok(t_tok *lst);
void	ft_lstadd_back_tok(t_tok **lst, t_tok *new, int *err);
void	expand_tokens(t_tok **lst_tok, int *err);
void	ft_print_list_tok(t_tok **lst_tok);
int		msg_error_parsing(int type, int *err);
int		create_process(t_proc **lst_proc, t_tok **lst_tok, int *err);
t_proc	*ft_lstnew_proc(int *err);
t_proc	*ft_lstlast_proc(t_proc *lst);
void	ft_lstadd_back_proc(t_proc **lst, t_proc *new, int *err);
void	ft_print_process(t_proc **lst_proc);
void	sep_process(t_proc **lst_proc, t_tok **lst_tok);


/*exec and process functions*/
void	pipefd_calibrate(t_exec **exec);
void	launch_process(t_exec **exec, t_proc **pcs_chain);
void	command_process(t_proc **pcs_chain, t_exec **exec, int pos);
void	launch_process(t_exec **exec, t_proc **pcs_chain);
void	wait_processes(t_exec *exec);
char	*exec_path(char **all_path, t_proc *exec_trgt);
void	execve_bash(t_proc **exec_trgt, t_exec **exec);

/*utils for process and env*/
void	init_exec(t_exec *exec, t_proc *pcs_chain, char **env);
int		measure_list(t_proc *lst);
void	redirect_input(int	input_fd);
void	redirect_output(int output_fd);
void	close_all_pipes(t_exec *exec);

/* exec total malloc : pids, pipes, valid_path,   */
#endif
