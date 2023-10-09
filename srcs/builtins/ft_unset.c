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

int	check_syntax_unset(char *var);
/*
we look in the environment for a variable to delete
1. if incorrect syntax, don't do anythong and goes to nex arg
2. if correct and the variable is found in the env (like USER) return index
3. execute the downsiwe_env (copy everything from current env execpt the index
    of target)
*/
int ft_unset(t_exec *exec, char **arg)
{
	int	i;
	int idx;

	if (!exec || !arg || !arg[1])
		return (0);
	i = 1;
	while (arg[i])
	{
		
		if (check_syntax_unset(arg[i]))
		{
			idx = search_env_var(exec->env, arg[i]);
			if (idx != -1)
				exec->env = downsize_env(exec->env, idx, 0, 0);
		}
		i++;
	}
	return (0);	
}

/*
same as for export builtin but without '=' mandatory
*/
int	check_syntax_unset(char *var)
{
	int	i;

	if (!var)
		return (0);
	if (!ft_isalpha(var[0]) && var[0] != '_')
	{
		printf("minishell: export: `%s': not a valid identifier\n", var); //replace by official minishell name
		return (0);
	}
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