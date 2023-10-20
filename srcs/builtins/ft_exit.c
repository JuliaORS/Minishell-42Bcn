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

/*
receive a string and a nb pointer as input traverse the string while space and
return the sign if + or - encountered after spaces
update pointer value to where stopped in the string (after first sign for 
instance)
*/
int	traverse_blank(const char *str, int *n)
{
	int sign;
	int	i;

	sign = 1;
	i = *n;
	while (str[i] && (str[i] == 32 || (9 <= str[i] && str[i] <= 13)))
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (n)
		*n = i;
	return (sign);
}

/*
this to check if a number is valid 
traverse the string as long as digit and flag that a digit was encountered
if first non-zero encountered, start measuring. then traverse all the space
if the string is not terminated (i.e  contained a non-digit or non-space), if
it never encountered a number (never started looop) or if the number is 
bigger than upper base 10 limit of LONG_MAX -> invalid
 */
int valid_number(const char *str)
{
	int contain_int;
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
	if ( contain_int == 0 || nb_len > 19 || *str != '\0')
		return (1);
	return (0);
}
/*
traverse the string and return if valid :
need to contain number no bigger than LONG MAX
special case for first character that can be + or -0
we start by traversing space, then see if + or - we traverse it as well.
then send to number validation check
*/

int	check_arg(const char *arg, int i)
{
	int	contain_int;
	int	nb_len;

	contain_int = 0;
	nb_len = 0;
	if (arg[0] == '\0')
		return (1);
	while (arg[i] == 32 || (9 <= arg[i] && arg[i] <= 13))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (valid_number(&arg[i]) == 1)
		return (1);
	return (0);
}
int	ft_atoi_checker(const char *str, int *flag)
{
	int		i;
	int		sign;
	unsigned long long	result;

	i = 0;
	result = 0;
	if(check_arg(str, 0))
		return (*flag = -1);
	sign = traverse_blank(str, &i);
	while (str[i] != '\0' && ('0' <= str[i] && str[i] <= '9'))
	{
		result = result * 10;
		result = result + (str[i] - '0');
		if (sign == 1 && result > LONG_MAX)
			return (*flag = -1);
		else if (sign == -1 && result > -(unsigned long)LONG_MIN)
			return (*flag = -1);
		i++;
	}
	result = result * sign;
	return (result);
}

/*to put in a general utils for errors*/
int	exit_err_msg(char *msg, int n, t_exec *exec, char **arg)
{
	if (arg[1] && !arg[2])
		ft_printf(STDERR_FILENO, "minishell: exit: %s: %s\n", arg[1], msg);
	else if (arg[1] && arg[2] && n == 255)
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
	if (isatty(STDIN_FILENO) && exec->in_parent == 1)
	{
		ft_printf(STDERR_FILENO, "exit\n");
		clear_history();
	}
	if (!arg[1])
	{
		if (exec->exit[1] > 0)
			exec->exit[0] = exec->exit[1];
		else
			exec->exit[0] = 0;
		free_exec(&exec);
		exit(exec->exit[0]);
	}
	n = ft_atoi_checker(arg[1], &flag);
	if (flag == -1)
		exit_err_msg("numeric argument required", 255, exec, arg);
	if (arg[2])
		return (exit_err_msg("too many arguments", 1, exec, arg));
	exit(n);
}
