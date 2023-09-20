/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:25:15 by julolle-          #+#    #+#             */
/*   Updated: 2023/08/02 12:30:00 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*d;

	i = -1;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (!len || d == s)
		return (dst);
	if (d > s)
	{
		while (len > 0)
		{
			len--;
			d[len] = s[len];
		}
	}
	else
	{
		while (++i < len)
			d[i] = s[i];
	}
	return (dst);
}

/*int   main(void)
{
    char dest[70] = "This is string.h library function";
	char src[20] = "holaquetal";
	ft_memmove(dest, src, 5);
    return (0);
}*/
