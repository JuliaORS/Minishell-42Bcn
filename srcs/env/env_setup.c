/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:28:28 by rjobert           #+#    #+#             */
/*   Updated: 2023/09/27 13:28:31 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
duplicate envrionment from main to run our minishell
1. allocate memory for array of char * for as many varble as in **env, using 
	count_var_env and ft_calloc
2. traverse the env array and make a deep copy with ft_strdup of each line into 
	our newly created array
3. clean exit if malloc issue and return NULL
4. return the duplicate environment
*/
char	**env_dup(char **env, int i, int j)
{
	char	**env_dup;
	int		size;

	size = count_var_env(env);
	env_dup = ft_calloc(size + 1, sizeof(char *));
	if (!env_dup)
		return (NULL);
	while (env[i])
	{
		env_dup[j] = ft_strdup(env[i]);
		if (!env_dup[j])
		{
			free_env(env_dup);
			return (NULL);
		}
		i++;
		j++;
	}
	env_dup[i] = NULL;
	return (env_dup);
}

/*
count how many env variable in char *array. 
to serve when we want to allocate memory to cpy or mdify the env duplciated
iterate if not null and until not null
*/
int	count_var_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

/*
clean a mallocated environment, extra redundancy to avoid segfaut
and freeing non-allocated char *.
*/
void	free_env(char	**env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (env[i])
			free(env[i]);
		i++;
	}
	if (env)
		free(env);
}

/*
builtin to display current environement
*/
int	ft_env(t_exec *exec, char **arg)
{
	int	i;

	if (arg && arg[1])
	{
		ft_printf(STDERR_FILENO, "env: %s: command not found\n", arg[1]);
		return (1);
	}
	i = 0;
	while (exec->env && exec->env[i] && i < count_var_env(exec->env))
	{
		printf("%s\n", exec->env[i]);
		i++;
	}
	return (0);
}

/*
look for a variable in env and return its key=value pair
*/
char	*ft_getenv(char **env, char *target)
{
	int	i;
	int	idx;

	if (!env)
		return (NULL);
	i = 0;
	idx = search_env_var(env, target);
	if (idx == -1)
		return (NULL);
	else
		return (env[idx]);
}
