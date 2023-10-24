/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:50:37 by rjobert           #+#    #+#             */
/*   Updated: 2023/05/23 14:40:17 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_parse_type(char c, va_list arg_list, int fd)
{
	int	n;

	if (c == 'c')
		n = ft_putchar(va_arg(arg_list, int), fd);
	else if (c == 's')
		n = ft_putstr(va_arg(arg_list, char *), fd);
	else if (c == 'i' || c == 'd')
		n = ft_print_nbr(va_arg(arg_list, int), fd);
	else if (c == '%')
		n = ft_putchar('%', fd);
	else if (c == 'x')
		n = ft_hexprint(va_arg(arg_list, unsigned int), 1, fd);
	else if (c == 'X')
		n = ft_hexprint(va_arg(arg_list, unsigned int), 0, fd);
	else if (c == 'u')
		n = ft_print_ui(va_arg(arg_list, unsigned int), fd);
	else if (c == 'p')
		n = ft_print_ptr(va_arg(arg_list, void *), fd);
	else
		return (-1);
	return (n);
}

static int	ft_iterate_measure(const char *s, va_list arg_list, int n, int fd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1])
		{
			n = ft_parse_type(s[i + 1], arg_list, fd);
			i += 2;
		}
		else
		{
			n = ft_putchar(s[i], fd);
			i += n;
		}
		if (n == -1)
			return (-1);
		else
			count += n;
	}
	return (count);
}

int	ft_printf(int fd, const char *s, ...)
{
	int		i;
	int		n;
	va_list	arg_list;

	i = 0;
	n = 0;
	va_start(arg_list, s);
	if (!s)
		return (-1);
	n = ft_iterate_measure(s, arg_list, n, fd);
	va_end(arg_list);
	return (n);
}
