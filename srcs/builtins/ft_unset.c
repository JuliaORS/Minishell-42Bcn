/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:10:50 by rjobert           #+#    #+#             */
/*   Updated: 2023/10/27 14:10:54 by rjobert          ###   ########.fr       */
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
int	ft_unset(t_exec *exec, char **arg)
{
	int	i;
	int	idx;

	if (!exec || !arg || !arg[1])
		return (0);
	i = 1;
	while (arg[i])
	{
		if (check_syntax_unset(arg[i]))
		{
			idx = search_env_var(exec->env, arg[i]);
			if (idx != -1)
			{
				exec->env = downsize_env(exec->env, idx, 0, 0);
				if (!exec->env)
					ft_printf(STDERR_FILENO, \
						"minishell: unset: calloc failed\n");
			}
			delete_node_xpenv(&exec->exp_env, arg[i], NULL);
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
		ft_printf(STDERR_FILENO, \
			"minishell: unset: `%s': not a valid identifier\n", var);
		return (0);
	}
	i = -1;
	while (var[++i])
	{
		if ((!ft_isalnum(var[i]) && !(var[i] == '_')) || var[i] == '=')
		{
			ft_printf(STDERR_FILENO, \
				"minishell: unset: `%s': not a valid identifier\n", var);
			return (0);
		}
	}
	return (1);
}
