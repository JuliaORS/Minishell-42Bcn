/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:01:15 by julolle-          #+#    #+#             */
/*   Updated: 2023/03/06 15:19:17 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr(unsigned long long ptr)
{
	char	*bhex;
	int		len;
	int		i;
	char	*strhex;

	i = 0;
	len = ft_hexnumlen(ptr);
	strhex = (char *)malloc(sizeof(char) * (len + 1));
	if (!strhex)
		return (-1);
	strhex[len] = '\0';
	len = len - 1;
	bhex = "0123456789abcdef";
	while (ptr > 0)
	{
		strhex[len] = bhex[ptr % 16];
		ptr = ptr / 16;
		len--;
	}
	i = ft_printstr(strhex);
	free (strhex);
	return (i);
}

int	ft_printptr(unsigned long long ptr)
{
	int	i;
	int	res;

	res = 0;
	i = ft_printstr("0x");
	if (i == -1)
		return (-1);
	else if (ptr == 0)
		i = i + ft_printchar('0');
	else
	{
		res = ft_putptr(ptr);
		if (res == -1)
			return (-1);
		else
			i = res + i;
	}
	return (i);
}
