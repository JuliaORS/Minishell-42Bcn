
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:15:32 by rjobert           #+#    #+#             */
/*   Updated: 2023/09/25 12:15:35 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
check that the string respect the variabel environment syntax
1. doesn't start by anything else than alpahbets or '_'
2. followed by alphanumericals or '_'
3. contains at least one '='
4. return an error 'invalid identifier' only if case 1 and 2 wrong
*/
int	check_syntax_export(char *var)
{
	int	i;
	int	valid;

	if (!var)
		return (0);
	if (!ft_isalpha(var[0]) && var[0] != '_')
	{
		printf("minishell: export: `%s': not a valid identifier\n", var); //replace by official minishell name
		return (0);
	}
	i = -1;
	valid = 0;
	while(var[++i])
		if (var[i] == '=')
			valid = 1;
	if (valid == 0)
		return (0);
	i = -1;
	while (var[++i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			printf("minishell: export: `%s': not a valid identifier\n", var); //replace by official minishell name
			return (0);
		}
	}
	return (1);
}

/*
1. if there is no argument, print the environment with "declare -x" prefix
2. check that variable follow bash syntax requirement (start with alpha or '_')
	and following workds only alpha or "_"
3. look if the variable already exist. if it doesn't use funciton realloc_mem_env
	to allocate same memory of current env + 1 char * and copy our env then add 
	variable. then free previous env
 3.b - Otherwise, if the var already exist, we look for the part after the '=' 
 example :
 runing export USER=bobmorane TERM=aventurier 123 _76
 would change the two variable USER and TERM, display errror for 123 and 
 do nothing for _75 (as valid syntax but no '=' sign)

*/
int	ft_export(t_exec *exec, char **arg)
{
		int		i;
		int		idx;

		if (!exec->env)
			return (0);
		i = -1;
		if (!arg[1])
		{
			while(exec->env && exec->env[++i])
				printf("declare -x %s\n", exec->env[i]);
			return (0);
		}
		i = 0;
		while (arg && arg[++i])
		{
			if (check_syntax_export(arg[i]))
			{
				idx = search_env_var(exec->env, extract_variable(arg[i]));
				if (idx == -1 )
					exec->env = realloc_env(exec->env, arg[i]);
				else
				{
					free(exec->env[idx]);
					exec->env[idx] = ft_strdup(arg[i]);
					if (!exec->env[idx]) //HANDLE MALLOC DEEEPER HERE
						return (-1);
				}
			}
		}
		return (0);
}