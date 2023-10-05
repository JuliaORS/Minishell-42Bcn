/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:33:10 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/03 13:14:15 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	lend;
	unsigned int	j;
	unsigned int	result;

	lend = 0;
	j = 0;
	result = 0;
	while (dst[lend] != '\0')
		lend++;
	while (src[result] != '\0')
		result++;
	if (dstsize <= lend)
		result = result + dstsize;
	else
		result = result + lend;
	while (src[j] != '\0' && (lend + 1) < dstsize)
	{
		dst[lend] = src[j];
		j++;
		lend++;
	}
	dst[lend] = '\0';
	return (result);
}
