/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_modify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:28:54 by rjobert           #+#    #+#             */
/*   Updated: 2023/09/27 13:28:56 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
increas the memory size of env array by one char * and copy it*/
char	**realloc_mem_env(char **env, char *var)
{
	char	**new_env;
	char	*temp;
	int		i;
	size_t	size;

	size = count_var_env(env) + 1;
	new_env = ft_calloc(size + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env && env[i])
	{
		temp = ft_strdup(env[i]);
		free(env[i]);
		new_env[i] = temp;
		i++;
	}
	new_env[size] = NULL;
	new_env[size - 1] = var;
	free(env);
	return(new_env);
}
/*
we allocate memory of previous array size - 1 (as we will delete
one char *). We then we traverse the array and look at each variable 
by extracting its characters before the '='. if they match, the term 
we are looking for we skip it (don't copy it, otherwise wed do a deep copy).
meanwhile we delete the previous environment

*/
char	**dealloc_mem_env(char **env, char *var)
{
	char	**new_env;
	char	*temp;
	int		i;
	size_t	size;

	size = count_var_env(env) - 1;
	new_env = ft_calloc(size + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env && env[i])
	{
		temp = extract_variable(env[i]);
		if (ft_strncmp(temp, var, ft_strlen(var)) ** temp)
			i++;
		free(temp);
		temp = ft_strdup(env[i]);
		free(env[i]);
		new_env[i] = temp;
		i++;
	}
	new_env[size] = NULL;
	free(env);
	return(new_env);
}

/*
search for the variable in the environment
and return the index if found, -1 otherwise
*/
int	search_env_var(char **env, char *var)
{
	int	i;
	char *var_extract;

	if (!env)
		return (-1);
	i = 0;
	while (env && env[i])
	{
		var_extract = extract_variable(env[i]);
		if (!ft_strncmp(var_extract, var, ft_strlen(var)) && var_extract)
		{
			free(var_extract);
			return(i);
		}
		free(var_extract);
		i++;
	}
	return (-1);
}
/*
traverse key_value char * and return the substring of all characters
before the '=', if no '=' encountered return NULL
*/
char	*extract_variable(char *key_value)
{
	char *var;
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (key_value[i])
	{
		if (key_value[i] == '=')
			len = i;
		i++;
	}
	if (len == 0)
		return (NULL);
	return (ft_substr(key_value, 0, len - 1));
}

