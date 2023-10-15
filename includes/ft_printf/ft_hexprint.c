/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:35:10 by rjobert           #+#    #+#             */
/*   Updated: 2023/05/23 15:06:28 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	size_hex(unsigned int n)
{
	int	size;

	if (n < 0 || n == 0)
		size = 1;
	else
		size = 0;
	while (n)
	{
		size ++;
		n /= 16;
	}
	return (size);
}

int	ft_hexprint(unsigned int n, int maj, int fd)
{
	char			*base_16;
	int				size;

	size = size_hex(n);
	if (maj == 0)
		base_16 = "0123456789ABCDEF";
	else
		base_16 = "0123456789abcdef";
	if (n < 16)
	{
		if (ft_putchar(base_16[n], fd) == -1)
			return (-1);
	}
	else
	{
		if (ft_hexprint(n / 16, maj, fd) == -1)
			return (-1);
		if (ft_hexprint(n % 16, maj, fd) == -1)
			return (-1);
	}
	return (size);
}
