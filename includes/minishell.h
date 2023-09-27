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
t_tok	*ft_lstnew_tok(char *str, int type);
void	ft_lstadd_back_tok(t_tok **lst, t_tok *new);
t_proc	*ft_lstnew_proc();
t_proc	*ft_lstlast_proc(t_proc *lst);
void	ft_lstadd_back_proc(t_proc **lst, t_proc *new);
int		create_tokens(t_tok **lst_tok, char *line);
void	ft_print_list(t_tok *lst_tok);
void	ft_print_process(t_proc *lst_proc);
void	sep_process(t_proc **lst_proc, t_tok **lst_tok);

#endif
