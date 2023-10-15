/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:03:47 by rjobert           #+#    #+#             */
/*   Updated: 2023/05/23 14:44:14 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_nbr(int n, int fd)
{
	int		size;
	char	*nbr;

	if (n < 0 || n == 0)
		size = 1;
	else
		size = 0;
	nbr = ft_itoa(n);
	if (!nbr)
		return (-1);
	if (ft_putstr(nbr, fd) == -1)
	{
		free (nbr);
		return (-1);
	}
	while (n)
	{
		size++;
		n /= 10;
	}
	free (nbr);
	return (size);
}
