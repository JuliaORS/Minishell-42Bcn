/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:05:56 by julolle-          #+#    #+#             */
/*   Updated: 2023/08/02 12:26:46 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	strlend(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	sizen;

	i = 0;
	sizen = strlend(needle);
	if (needle[i] == '\0')
		return ((char *)haystack);
	if (haystack[i] == '\0')
		return (0);
	if (sizen > len)
		return (NULL);
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		if (needle[j] == haystack[i])
		{
			while (needle[j] == haystack[i + j] && j < sizen && (i + j) < len)
				j++;
			if (j == sizen)
				return (&((char *)haystack)[i]);
		}
		i++;
	}
	return (0);
}
