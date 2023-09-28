/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:15:32 by rjobert           #+#    #+#             */
/*   Updated: 2023/09/28 12:15:35 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_arg_flag(char **arg)
{
	if (!arg)
		return (-1);
	if (arg && arg[1])
	{
		if (!ft_strncmp(arg[1], "-n", 3))
			return (1);
		else 
			return (0);
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
void	ft_echo(t_exec *exec, char **arg)
{
	int	i;
	int	flag;

	(void) exec;
    flag = check_arg_flag(arg);
    i = 1;
    if (flag == 1)
        i = 2;
	if (arg[1])
	{
		while (arg && arg[i])
		{
			printf("%s", arg[i]);
			if (arg[i + 1])
				printf(" ");
			i++;
		}
	}
	if (flag == 1)
		return ;
	printf("\n");
}