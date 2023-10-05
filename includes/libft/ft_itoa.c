/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:09:50 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/03 13:13:19 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_numlen(long num)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		num = num * -1;
		len++;
	}
	while (num > 0)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

char	*ft_string(long n, char *s, int len)
{
	while (n > 0)
	{
		s[len] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	long	num;
	char	*s;
	int		len;

	num = n;
	len = ft_numlen(num);
	s = (char *) malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	s[len] = '\0';
	len = len - 1;
	if (num == 0)
	{
		s[0] = 48;
		return (s);
	}
	else if (num < 0)
	{
		s[0] = '-';
		num = num * -1;
	}
	ft_string(num, s, len);
	return (s);
}
