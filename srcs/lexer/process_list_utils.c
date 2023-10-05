/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:25:38 by julolle-          #+#    #+#             */
/*   Updated: 2023/09/28 14:48:00 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

<<<<<<< HEAD:srcs/lexer/process_list_utils.c
#include "../../includes/minishell.h"
=======
#include "minishell.h"
>>>>>>> 2f9d0cd5e14ec518c3a7aa6a5d05b1bd598a2bb2:srcs/process_list_utils.c

t_proc	*ft_lstnew_proc(int *err)
{
	t_proc	*newcont;

	newcont = malloc(sizeof(t_proc));
	if (!newcont)
	{
		msg_error_parsing(12, err);
		return (NULL);
	}
	newcont->arg = NULL;
	newcont->pos = 0;
	newcont->fd[0] = 0;
	newcont->fd[1] = 0;
	newcont->intype = -1;
	newcont->infile = NULL;
	newcont->outfile = NULL;
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

void	ft_lstadd_back_proc(t_proc **lst, t_proc *new, int *err)
{
	t_proc	*tmp;

	if (*err)
		return ;
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
