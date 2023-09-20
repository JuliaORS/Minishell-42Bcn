/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:12:28 by julolle-          #+#    #+#             */
/*   Updated: 2023/09/19 16:38:25 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tok	*ft_lstnew_msh(int type)
{
	t_tok	*newcont;

	newcont= malloc(sizeof(t_tok));
	if (!newcont)
		return (NULL);
    newcont->arg = NULL;
    newcont->type = type;
    newcont->namefile = NULL;
	newcont->next = NULL;
	return (newcont);
}

void	ft_lstadd_back_msh(t_tok **lst, t_tok *new)
{
    if (lst != NULL)
	{
		if (*lst != NULL)
			ft_lstlast(*lst)->next = new;
		else
			*lst = new;
	}
    else
    {
        
    }
}
