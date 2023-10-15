/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:06:06 by rjobert           #+#    #+#             */
/*   Updated: 2023/10/13 11:06:09 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	traverse_blank(const char *str, int *n)
{
	int sign;
	int	i;

	sign = 1;
	i = *n;
	while (str[i] == 32 || (9 <= str[i] && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	return (sign);
}
int	check_arg(const char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if(!ft_isdigit(arg[i]))
			return (1);
		i++;
	}
	if (i > 13)
		return (1);
	return (0);
}
int	ft_atoi_checker(const char *str, int *flag)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	result = 0;
	if(check_arg(str))
		return (*flag = -1);
	sign = traverse_blank(str, &i);
	while (str[i] != '\0' && ('0' <= str[i] && str[i] <= '9'))
	{
		result = result * 10;
		result = result + (str[i] - '0');
		if (result > INT_MAX || result < INT_MIN)
			return (*flag = -1);
		i++;
	}
	result = result * sign;
	return (result);
}

int	exit_err_msg(char *msg, int n, t_exec *exec, char **arg)
{
	if (exec->in_parent == 1)
		printf("exit\n");
	if (arg[1] && !arg[2])
		ft_printf(STDERR_FILENO, "minishell: exit: %s: %s\n", arg[1], msg);
	else
		ft_printf(STDERR_FILENO, "minishell: exit: %s\n", msg);
	if (n == 255)
		exit(n);
	else if (exec->in_parent == 1)
		return (n);
	free_exec(&exec);
	exit (n);
}
/*
-if no argument: exit program with zero 
-if one argument : check that only contain number and no overflow:
	if so -> exit with error 255 with numeric argument msg
-if first argument number and following by other : in parent 
don't exit, return 1 with message too many params. if in children 
exit
- display "exit" before exiting only in parent
*/
int ft_exit(t_exec *exec, char **arg)
{
	int	flag;
	int	n;

	flag = 0;
	if (!arg[1])
	{
		exec->exit[0] = 0;
		free_exec(&exec);
		if (exec->in_parent == 1)
			printf("exit\n");
		exit(exec->exit[0]);
	}
	n = ft_atoi_checker(arg[1], &flag);
	if (flag == -1)
		exit_err_msg("numeric argument required", 255, exec, arg);
	if (arg[2])
		return (exit_err_msg("too many arguments", 1, exec, arg));
	printf("exit\n");
	exit(n);
}
