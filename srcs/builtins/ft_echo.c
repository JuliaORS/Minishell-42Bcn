/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:09:48 by rjobert           #+#    #+#             */
/*   Updated: 2023/10/27 14:09:52 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
because echo -n can also be echo -nnnnnnnn but no echo -nnnnnannnn
*/
int	check_flag(char *arg)
{
	int	i;

	if (!arg)
		return (-1);
	if (arg && arg[1])
	{
		if (arg[0] != '-')
			return (0);
		i = 1;
		while (arg[i] == 'n')
			i++;
		if (arg[i] == '\0')
			return (1);
	}
	return (0);
}

/*
	receive arguments array and execute eco-like function
	1. if second argument is not -n, execute echo on all following
		value in array of args until it is NULL starting at arg[1] 
	2. if second argument is -n -> flag value is 1 and no trailing nl
		and array of words to echo start at arg[2] in the 
		array of arguments. 
    3. words are separated by a space until the 
		last word
*/
int	ft_echo(t_exec *exec, char **arg)
{
	int	i;
	int	flag;

	(void) exec;
	flag = 0;
	if (arg && arg[1])
		flag = check_flag(arg[1]);
	i = 0;
	if (flag == 1)
		i = 1;
	if (arg[++i])
	{
		while (check_flag(arg[i]))
			i++;
		while (arg && arg[i])
		{
			if (arg[i])
				ft_putstr_fd(arg[i], STDOUT_FILENO);
			if (arg[++i])
				write(STDOUT_FILENO, " ", 1);
		}
	}
	if (flag == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
