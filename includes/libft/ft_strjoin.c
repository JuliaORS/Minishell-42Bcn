/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:00:27 by julolle-          #+#    #+#             */
/*   Updated: 2023/03/08 11:05:33 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, (char *)s1, ft_strlen(s1) + 1);
	ft_strlcat(str, (char *)s2, ft_strlen(str) + ft_strlen(s2) + 1);
	return (str);
}

/*int	main (void)
{
	char s1[4] = "que";
	char s2[8] = "q";
	char *str1 = malloc(sizeof(char) * 5);
	char *str2 = malloc(sizeof(char) * 5);
	str1 = "ho";
	str2 = "como";
	printf("%s \n", ft_strjoin(str1, str2));
	return (0);
}*/
