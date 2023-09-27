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
char	**env_dup(char **env)
{
	char	**env_dup;
	int		i;
	size_t	size;

	size = count_var_env(env);
	env_dup = ft_calloc(size + 1, sizeof(char *));
	if (!env_dup)
		return (NULL);
	i = 0;
	while (env && env[i])
	{
		env_dup[i] = ft_strdup(env[i]);
		if (!env_dup)
		{
			free_env(env_dup);
			return (NULL);
		}
		i++;
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
	while(env && env[i])
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
	while(env && env[i])
	{
		if (env[i])
			free(env[i]);
		i++;
	}
	if (env)
		free(env);
}

