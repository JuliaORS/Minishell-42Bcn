
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

int		check_concat_valid(const char *var);
int		export_exec(t_exec *exec, char *arg, int type);
char	*extract_value(char *key_value);
char	*build_env_var(char *arg, t_exec *exec, int type, int idx);

/*
check that the string respect the variabel environment syntax
1. doesn't start by anything else than alpahbets or '_'
2. followed by alphanumericals or '_'
3. contains at least one '=' or '+='
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
		ft_printf(STDERR_FILENO, "minishell: export: `%s': not a valid identifier\n", var); 
		return (-1);
	}
	i = -1;
	while (var[++i] && !(var[i] == '=' || ((var[i]) == '+' && var[i + 1] == '=')))
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			ft_printf(STDERR_FILENO, "minishell: export: `%s': not a valid identifier\n", var); 
			return (-1);
		}
	}
	valid = check_concat_valid(var);
	return (valid);
}
/*
Traverse the string, if see += return 2, if see only = return 1
otherwise return 0
*/
int	check_concat_valid(const char *var)
{
	int	i;
	int	valid;

	i = -1;
	valid = 0;
	while(var[++i])
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
		int		type;

		exec->exit[0] = EXIT_SUCCESS;
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
			type = check_syntax_export(arg[i]);
			if (type < 0)
				exec->exit[0] = EXIT_FAILURE;
			if (type > 0)
				export_exec(exec, arg[i], type);
		}
	return (exec->exit[0]);
}

/*
based on the type of export or concat, we search for the occurence of the 
variable in env. if not found (index returned -1) we add it
if it is found -> if export mode classic we remplace, if concat mode we
add it to the current value
*/
int	export_exec(t_exec *exec, char *arg, int type)
{
	int		idx;
	char	*temp_arg;
	
	idx = search_env_var(exec->env, extract_variable(arg));
	temp_arg = build_env_var(arg, exec, type, idx);
	if (idx >= 0 && exec->env[idx])
	{
		free_pntr(exec->env[idx]);
		exec->env[idx] = ft_strdup(temp_arg);
	}
	else	
		exec->env = realloc_env(exec->env, temp_arg);
	free_pntr(temp_arg);
	if (!exec->env[idx])
		return (-1);
	return (0);
}

char	*build_env_var(char *arg, t_exec *exec, int type, int idx)
{
	char	**tmp;
	char	*env_var;
	
	env_var = NULL;
	tmp = key_val_pair(arg);
	if (tmp[1] == NULL)
		tmp[1] = "";
	if (type == 2 && idx >= 0)
		env_var = ft_strjoin(exec->env[idx], tmp[1]);
	if (idx < 0)
		env_var = ft_strdup(arg);
	else if (type == 1 && idx >= 0)
	{
		env_var = ft_strjoin(extract_variable(arg), "=");
		if (!env_var)
		{
			free_key_val(tmp);
			return (NULL);
		}
		env_var = ft_strjoin(env_var, tmp[1]);
	}
	free_key_val(tmp);
	if (!env_var)
		return (NULL);
	return (env_var);
}
