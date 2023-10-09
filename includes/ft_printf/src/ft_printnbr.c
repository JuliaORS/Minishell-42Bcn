/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:12:09 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/02 20:52:56 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_numlen_pf(long long int num)
{
	int	len;

	len = 0;
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

char	*ft_string_pf(long long int n, char *s, int len)
{
	while (n > 0)
	{
		s[len] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (s);
}

char	*ft_litoa(long long int n)
{
	long long int	num;
	char			*s;
	int				len;

	num = n;
	len = ft_numlen_pf(num);
	s = (char *) malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	s[len] = '\0';
	len = len - 1;
	if (num < 0)
	{
		s[0] = '-';
		num = num * -1;
	}
	ft_string_pf(num, s, len);
	return (s);
}

int	ft_printnbr(int nbr)
{
	char	*str;
	int		i;

	if (nbr == 0)
		return (ft_printchar('0'));
	if (nbr == -2147483648)
	{
		if ((write (1, "-2147483648", 11)) == -1)
			return (-1);
		else
			return (11);
	}
	else
	{
		str = ft_litoa(nbr);
		if (!str)
			return (-1);
		i = ft_printstr(str);
		free (str);
		return (i);
	}
}
