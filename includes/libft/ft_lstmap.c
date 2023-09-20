/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:40:30 by julolle-          #+#    #+#             */
/*   Updated: 2023/08/02 15:30:01 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*tmp;
	void	*content; 

	result = NULL;
	while (lst != NULL) 
	{
		content = f(lst->content);
		if (!content)
		{
			ft_lstclear(&result, del);
			return (NULL);
		}
		tmp = ft_lstnew(content);
		if (!tmp)
		{
			free (content);
			ft_lstclear(&result, del);
			return (NULL);
		}
		ft_lstadd_back(&result, tmp);
		lst = lst->next;
	}
	return (result);
}
