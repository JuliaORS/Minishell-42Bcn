/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:27:34 by julolle-          #+#    #+#             */
/*   Updated: 2023/02/20 15:51:26 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_recur(long nb, int fd)
{
	if (nb < 0)
	{
		nb = nb * -1;
		ft_putchar_fd('-', fd);
	}
	if (nb > 9)
	{
		ft_recur(nb / 10, fd);
		ft_recur(nb % 10, fd);
	}
	if (nb <= 9)
		ft_putchar_fd(nb + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	ft_recur(n, fd);
}
