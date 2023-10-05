/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:24:48 by julolle-          #+#    #+#             */
/*   Updated: 2023/09/28 14:44:22 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

<<<<<<< HEAD:srcs/lexer/token_list_utils.c
#include "../../includes/minishell.h"
=======
#include "minishell.h"
>>>>>>> 2f9d0cd5e14ec518c3a7aa6a5d05b1bd598a2bb2:srcs/token_list_utils.c

t_tok	*ft_lstnew_tok(char *str, int type, int *err)
{
	t_tok	*newcont;

	newcont = malloc(sizeof(t_tok));
	if (!newcont)
	{
		msg_error_parsing(12, err);
		return (NULL);
	}
	newcont->str = str;
	newcont->type = type;
	newcont->prev = NULL;
	newcont->next = NULL;
	return (newcont);
}

t_tok	*ft_lstlast_tok(t_tok *lst)
{
	t_tok	*temp;

	temp = lst;
	if (!lst)
		return (NULL);
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	ft_lstadd_back_tok(t_tok **lst, t_tok *new, int *err)
{
	t_tok	*tmp;
	
	if (*err)
		return ;
	if (lst != NULL)
	{
		if (*lst != NULL)
		{
			tmp = ft_lstlast_tok(*lst);
			ft_lstlast_tok(*lst)->next = new;
			new->prev = tmp;
		}
		else
			*lst = new;
	}
}
