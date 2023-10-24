/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:05:02 by julolle-          #+#    #+#             */
/*   Updated: 2023/03/08 11:04:32 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newcont;

	newcont = malloc(sizeof(t_list));
	if (!newcont)
		return (NULL);
	newcont->content = content;
	newcont->next = NULL;
	return (newcont);
}
