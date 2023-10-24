/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 19:36:07 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/03 13:14:30 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	final;
	char	*str;

	i = 0;
	final = (ft_strlen(s1) -1);
	if (!s1 || !set)
		return (NULL);
	if (s1[i] == '\0')
		return (ft_strdup(s1));
	while (ft_strchr(set, s1[i]) && i <= final)
		i++;
	if (i > final)
		return (ft_strdup(s1 + final + 1));
	while ((ft_strchr(set, s1[final]) && final >= 0))
		final--;
	str = malloc(final - i + 2);
	if (!str)
		return (NULL);
	ft_strlcpy (str, &s1[i], final - i + 2);
	return (str);
}
