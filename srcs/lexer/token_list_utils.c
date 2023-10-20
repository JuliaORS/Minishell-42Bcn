/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:24:48 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/20 13:04:38 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	*ft_lstnew_tok(char *str, int type)
{
	t_tok	*newcont;

	newcont = malloc(sizeof(t_tok));
	if (!newcont)
		return (NULL);
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

void	ft_lstadd_back_tok(t_tok **lst, t_tok *new)
{
	t_tok	*tmp;

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

int	ft_lstsize_tok(t_tok *lst)
{
	int		i;
	t_tok	*temp;

	i = 0;
	temp = lst;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

int	new_tok(t_tok **lst_tok, char *str, int type, int *exit)
{
	t_tok	*new_tok_node;

	new_tok_node = ft_lstnew_tok(str, type);
	if (!new_tok_node)
		return (err_msg_parser(MALLOC_MESS, 12, 0, exit));
	ft_lstadd_back_tok(lst_tok, new_tok_node);
	return (0);
}
