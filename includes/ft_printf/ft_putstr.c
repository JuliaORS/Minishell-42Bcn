/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:54:13 by rjobert           #+#    #+#             */
/*   Updated: 2023/05/23 14:06:31 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s, int fd)
{
	int	size;
	int	i;

	if (!s)
	{
		s = "(null)";
	}
	i = 0;
	while (s[i])
	{
		if (ft_putchar(s[i], fd) == -1)
			return (-1);
		else
			i++;
	}
	size = ft_strlen(s);
	return (size);
}
