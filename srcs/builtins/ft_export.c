/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:10:17 by rjobert           #+#    #+#             */
/*   Updated: 2023/10/27 14:10:20 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_concat_valid(const char *var);
int		export_exec(t_exec *exec, char *arg, int type);
char	*extract_value(char *key_value);
char	*build_env_var(char *arg, t_exec *exec, int type, int idx);
char	*rebuild_var(char *env_var, char *tmp_var, char **tmp, char *arg);

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
		ft_printf(STDERR_FILENO, \
			"minishell: export: `%s': not a valid identifier\n", var);
		return (-1);
	}
	i = -1;
	while (var[++i] && !(var[i] == '=' || ((var[i]) == '+' && \
		var[i + 1] == '=')))
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			ft_printf(STDERR_FILENO, \
				"minishell: export: `%s': not a valid identifier\n", var);
			return (-1);
		}
	}
	valid = check_concat_valid(var);
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
	t_xpenv	*exp_env;

	exec->exit[0] = EXIT_SUCCESS;
	if (!arg[1])
	{
		exp_env = exec->exp_env;
		while (exp_env)
		{
			printf("declare -x %s\n", exp_env->var);
			exp_env = exp_env->next;
		}
		return (0);
	}
	i = 0;
	while (arg && arg[++i])
	{
		type = check_syntax_export(arg[i]);
		if (type < 0)
			exec->exit[0] = EXIT_FAILURE;
		else
			export_exec(exec, arg[i], type);
	}
	return (exec->exit[0]);
}

/*
based on the type of export or concat, we search for the occurence of the 
variable in env. if not found (index returned -1) we add it
if it is found -> if export mode classic we remplace, if concat mode we
add it to the current value, we then add it to exp_env data structure
*/
int	export_exec(t_exec *exec, char *arg, int type)
{
	int		idx;
	char	*temp_arg;

	if (type == 0)
	{
		add_expenv(&exec->exp_env, arg, type);
		return (0);
	}
	temp_arg = extract_variable(arg);
	idx = search_env_var(exec->env, temp_arg);
	free_pntr(temp_arg);
	temp_arg = build_env_var(arg, exec, type, idx);
	if (idx >= 0 && exec->env[idx])
	{
		free_pntr(exec->env[idx]);
		exec->env[idx] = ft_strdup(temp_arg);
	}
	else
		exec->env = realloc_env(exec->env, temp_arg);
	add_expenv(&exec->exp_env, temp_arg, type);
	free_pntr(temp_arg);
	if (idx >= 0 && !exec->env[idx])
		return (-1);
	return (0);
}

/*
Description:
The build_env_var function is designed to create or modify an 
env variable based on the provided arguments, existing environment, 
and type of operation specified (export or concatenate).

Parameters:
char *arg: The string containing the potential env var key-value pair.
t_exec *exec: our exec state stored in a struct
int type: An integer indicating the type of operation: (add, replace or concat)

Returns: a string representing the built or modified environment variable.
NULL if there is a failure in processing (like memory allocation errors)

-The function starts by splitting the arg into a key-value pair.
-If the type is 2 (concatenate) and the variable already exists in 
the environment (idx >= 0)
 it concatenates the new value to the existing value.
-If the variable doesn't exist in the environment (idx < 0) and is not 
concat (+=), it simply duplicates the arg.
- if it is dooesnt exist but is entered as concat (+= ) we use the rebuild
function
-If the type is 1 (replace or add) and the variable exists (idx >= 0), 
it replaces the value of the variable in the environment with the new value. 
The variable key and the = sign are added to this new value.
*/
char	*build_env_var(char *arg, t_exec *exec, int type, int idx)
{
	char	**tmp;
	char	*env_var;
	char	*tmp_var;

	env_var = NULL;
	tmp_var = NULL;
	tmp = key_val_pair(arg);
	if (tmp[1] == NULL)
		tmp[1] = "";
	if (type == 2 && idx >= 0)
		env_var = ft_strjoin(exec->env[idx], tmp[1]);
	else if (idx < 0 && type != 2)
		env_var = ft_strdup(arg);
	else if ((type == 1 && idx >= 0) || (idx < 0 && type == 2 ))
		env_var = rebuild_var(env_var, tmp_var, tmp, arg);
	free_key_val(tmp);
	if (!env_var)
		return (NULL);
	return (env_var);
}
/*
Extracts the variable name from arg using extract_variable() before = or +=.
Joins the extracted variable with =.
Joins the result with the value.
*/
char	*rebuild_var(char *env_var, char *tmp_var, char **tmp, char *arg)
{
	env_var = extract_variable(arg);
	tmp_var = ft_strjoin(env_var, "=");
	free_pntr(env_var);
	if (!tmp_var)
	{
		free_key_val(tmp);
		return (NULL);
	}
	env_var = ft_strjoin(tmp_var, tmp[1]);
	free_pntr(tmp_var);
	return (env_var);
}
