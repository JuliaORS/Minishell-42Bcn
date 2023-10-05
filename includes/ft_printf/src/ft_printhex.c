/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:21:33 by julolle-          #+#    #+#             */
/*   Updated: 2023/03/06 15:18:14 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexnumlen(unsigned long long num)
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
		num = num / 16;
		len++;
	}
	return (len);
}

int	ft_print_hex_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_printchar(str[i]) == -1)
		{
			free(str);
			return (-1);
		}
		else
			i++;
	}
	free(str);
	return (i);
}

int	ft_puthex(unsigned int nhex, const char flag)
{
	char	*blowhex;
	char	*buphex;
	int		len;
	char	*strhex;

	len = ft_hexnumlen(nhex);
	strhex = (char *)malloc(sizeof(char) * (len + 1));
	if (!strhex)
		return (-1);
	strhex[len] = '\0';
	len = len - 1;
	blowhex = "0123456789abcdef";
	buphex = "0123456789ABCDEF";
	while (nhex > 0)
	{
		if (flag == 'x')
			strhex[len] = blowhex[nhex % 16];
		else
			strhex[len] = buphex[nhex % 16];
		nhex = nhex / 16;
		len--;
	}
	return (ft_print_hex_str(strhex));
}

int	ft_printhex(unsigned int nhex, const char flag)
{
	if (nhex == 0)
		return (ft_printchar('0'));
	else
		return (ft_puthex(nhex, flag));
}
