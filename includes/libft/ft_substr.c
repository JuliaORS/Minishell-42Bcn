/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:41:44 by julolle-          #+#    #+#             */
/*   Updated: 2023/08/02 12:27:57 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (!s)
		return (NULL);
	if ((unsigned int)ft_strlen((char *)s) < start)
	{
		len = 0;
		start = 0;
	}
	else if ((unsigned int)ft_strlen((char *)(s + start)) < len)
		len = ft_strlen((char *)s + start);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, (s + start), (len + 1));
	return (str);
}
