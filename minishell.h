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
# include "includes/libft/libft.h"

typedef struct s_proc {
	char			**arg;
	int				fd[2];
	struct s_cmd	*prev;
	struct s_cmd	*next;
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
int		create_tokens(t_tok **lst_tok, char *line);
void	ft_print_list(t_tok *lst_tok);

#endif
