/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:23:18 by julolle-          #+#    #+#             */
/*   Updated: 2023/03/10 11:50:31 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_idflag(char const flag, va_list arg)
{
	if (flag == 'c')
		return (ft_printchar(va_arg(arg, int)));
	else if (flag == 's')
		return (ft_printstr(va_arg(arg, char *)));
	else if (flag == 'p')
		return (ft_printptr(va_arg(arg, unsigned long long)));
	else if (flag == 'd' || flag == 'i')
		return (ft_printnbr(va_arg(arg, int)));
	else if (flag == 'u')
		return (ft_printunbr(va_arg(arg, unsigned int)));
	else if (flag == 'x' || flag == 'X')
		return (ft_printhex(va_arg(arg, int), flag));
	else if (flag == '%')
		return (ft_printchar('%'));
	return (-1);
}

int	ft_check_str(char const *str, va_list arg, int i, int res)
{
	int	print;

	if (str[i] == '%')
	{
		print = ft_idflag(str[i++ + 1], arg);
		if (print == -1)
			return (-1);
		else
			res = res + print;
	}
	else
	{
		if (ft_printchar(str[i]) == -1)
			return (-1);
		else
			res++;
	}
	return (res);
}

int	ft_printf(char const *str, ...)
{
	int		res;
	int		i;
	va_list	arg;

	res = 0;
	i = 0;
	va_start(arg, str);
	while (str[i] != '\0')
	{
		res = ft_check_str(str, arg, i, res);
		if (res == -1)
			return (-1);
		else if (str[i] == '%')
			i++;
		i++;
	}
	va_end(arg);
	return (res);
}

/*int	main(void)
{
	unsigned int	nbr;
	int				i;
	int				a;
	//char *str;

	nbr = -14;
	//i = ft_printf("holque%p", ""); 
	i = ft_printf("hola %s\n", 12); 
	a = printf("hola %p\n", "");
	printf("\nhola %i", a);
	printf("\nhola %i", i);
	
	return (0);
}*/
