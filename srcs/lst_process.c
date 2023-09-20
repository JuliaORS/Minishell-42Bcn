/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:25:38 by julolle-          #+#    #+#             */
/*   Updated: 2023/09/20 15:27:09 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_proc	*ft_lstnew_proc(char *str, int type)
{
	t_proc	*newcont;

	newcont= malloc(sizeof(t_proc));
	if (!newcont)
		return (NULL);
    newcont->arg = str;
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