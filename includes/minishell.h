/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:05:20 by julolle-          #+#    #+#             */
/*   Updated: 2023/09/27 16:05:50 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "includes/libft/libft.h"

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

int		minishell(int argc, char **argv);
int		parsing_input(char *line, int *exit_status);
t_tok	*ft_lstnew_tok(char *str, int type, int *exit_status);
void	ft_lstadd_back_tok(t_tok **lst, t_tok *new, int *exit_status);
t_proc	*ft_lstnew_proc(void);
t_proc	*ft_lstlast_proc(t_proc *lst);
void	ft_lstadd_back_proc(t_proc **lst, t_proc *new);
int		create_tokens(t_tok **lst_tok, char *line, int *exit_status);
void	ft_print_list_tok(t_tok **lst_tok);
void	ft_print_process(t_proc **lst_proc);
void	create_process(t_proc **lst_proc, t_tok **lst_tok);
void	expand_tokens(t_tok **lst_tok);

#endif
