/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:34:24 by rjobert           #+#    #+#             */
/*   Updated: 2023/10/27 14:34:27 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
this to check if a number is valid 
traverse the string as long as digit and flag that a digit was encountered
if first non-zero encountered, start measuring. then traverse all the space
if the string is not terminated (i.e  contained a non-digit or non-space), if
it never encountered a number (never started looop) or if the number is 
bigger than upper base 10 limit of LONG_MAX -> invalid (nb_len > 19)
 */
int	valid_number(const char *str)
{
	int	contain_int;
	int	frst_nb;
	int	nb_len;

	contain_int = 0;
	frst_nb = 0;
	nb_len = 0;
	while (ft_isdigit(*str))
	{
		contain_int = 1;
		if (*str != '0')
			frst_nb = 1;
		if (frst_nb == 1)
			nb_len++;
		str++;
	}
	while (*str == 32)
		str++;
	if (contain_int == 0 || nb_len > 19 || *str != '\0')
		return (1);
	return (0);
}

/*
used in export
Traverse the string, if see += return 2, if see only = return 1
otherwise return 0
*/
int	check_concat_valid(const char *var)
{
	int	i;
	int	valid;

	i = -1;
	valid = 0;
	while (var[++i])
	{
		if (var[i] == '+')
		{
			if (var[i + 1] && var[i + 1] == '=')
				return (2);
		}
		if (var[i] == '=')
			valid = 1;
	}
	return (valid);
}
