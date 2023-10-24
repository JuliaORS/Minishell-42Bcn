/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itou.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:59:32 by rjobert           #+#    #+#             */
/*   Updated: 2023/05/23 14:49:36 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	number_bsize(unsigned int n)
{
	int	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*malloc_dynam(unsigned int nb, int size)
{
	char	*nbr;

	if (nb != 0)
		nbr = malloc(size + 1);
	else
		return (ft_strdup("0"));
	if (!nbr)
		return (NULL);
	nbr[size] = '\0';
	while (--size)
	{
		nbr[size] = nb % 10 + '0';
		nb /= 10;
	}
	nbr[0] = nb % 10 + '0';
	return (nbr);
}

static char	*ft_itoui(unsigned int n)
{
	char	*nbr;
	int		size;

	size = number_bsize(n);
	nbr = malloc_dynam(n, size);
	return (nbr);
}

int	ft_print_ui(unsigned int n, int fd)
{
	char	*n_str;
	int		size_base10;

	n_str = ft_itoui(n);
	if (!n_str)
		return (-1);
	if (ft_putstr(n_str, fd) == -1)
	{
		free(n_str);
		return (-1);
	}
	free(n_str);
	size_base10 = number_bsize(n);
	return (size_base10);
}
