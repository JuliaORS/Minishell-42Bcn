/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:34:20 by rjobert           #+#    #+#             */
/*   Updated: 2023/05/23 14:32:33 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hex_address(unsigned long long n, int fd);

int	ft_print_ptr(void *ptr, int fd)
{
	int	n;

	if (ft_putstr("0x", fd) == -1)
		return (-1);
	n = ft_hex_address((unsigned long long) ptr, fd);
	if (n != 0)
		return (n + 2);
	else
		return (3);
}

static int	size_hex_address(unsigned long long n)
{
	int	size;

	if (n < 0)
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

static int	ft_hex_address(unsigned long long n, int fd)
{
	char	*base_16;
	int		size;

	size = size_hex_address(n);
	base_16 = "0123456789abcdef";
	if (n < 16)
	{
		if (ft_putchar(base_16[n], fd) == -1)
			return (-1);
	}
	else
	{
		ft_hex_address(n / 16, fd);
		ft_hex_address(n % 16, fd);
	}
	return (size);
}
