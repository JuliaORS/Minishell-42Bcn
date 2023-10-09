/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:25:38 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/09 15:09:43 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_proc	*ft_lstnew_proc(void)
{
	t_proc	*newcont;

	newcont = malloc(sizeof(t_proc));
	if (!newcont)
		return (NULL);
	newcont->arg = NULL;
	newcont->pos = 0;
	newcont->fd[0] = 0;
	newcont->fd[1] = 0;
	newcont->intype = 0;
	newcont->infile = NULL;
	newcont->outfile = NULL;
	newcont->hd_lim = NULL;
	newcont->prev = NULL;
	newcont->next = NULL;
	return (newcont);
}

t_proc	*ft_lstlast_proc(t_proc *lst)
{
	t_proc	*temp;

	temp = lst;
	if (!lst)
		return (NULL);
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	ft_lstadd_back_proc(t_proc **lst, t_proc *new)
{
	t_proc	*tmp;

	if (lst != NULL)
	{
		if (*lst != NULL)
		{
			tmp = ft_lstlast_proc(*lst);
			ft_lstlast_proc(*lst)->next = new;
			new->prev = tmp;
		}
		else
			*lst = new;
	}
}
