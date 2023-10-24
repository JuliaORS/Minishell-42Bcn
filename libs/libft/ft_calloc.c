/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:06:02 by julolle-          #+#    #+#             */
/*   Updated: 2023/03/08 11:03:44 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*call;
	size_t	i;

	i = 0;
	call = malloc(size * count);
	if (call == NULL)
		return (NULL);
	else
	{
		while (i < size * count)
		{
			call[i] = '\0';
			i++;
		}
	}
	return (call);
}
