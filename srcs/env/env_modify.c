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

#include "minishell.h"

/*
increas the memory size of env array by one char * and copy it
*/
char	**realloc_env(char **env, char *var)
{
	char	**new_env;
	int		i;
	size_t	size;

	size = count_var_env(env) + 1; 
	new_env = ft_calloc(size + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env && env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		free(env[i]);
		i++;
	}
	new_env[size] = NULL;
	new_env[size - 1] = ft_strdup(var);
	free(env);
	return(new_env);
}
/*
we allocate memory of previous array size - 1 (as we will delete
one char *). We then we traverse the array and :
1. if the current variable is at the index we are looking to delete, we
free the char and increment the current env only
2. we copy the current index variable to the new_env position
3. we then free the past environment index
Then we delete the previous environment
*/
char	**downsize_env(char **env, int idx, int i, int j)
{
	char	**new_env;
	char	*temp;

	new_env = ft_calloc(count_var_env(env), sizeof(char *));
	if (!new_env)
		return (NULL);
	while (env && env[i])
	{
		temp = ft_strdup(env[i]);
		free(env[i]);
		if (i != idx)
		{
			new_env[j] = temp;
			j++;
		}
		else
			free(temp);
		i++;
	}
	new_env[j] = NULL;
	free(env);
	return(new_env);
}


/*
search for a target in the env, found it's index and repalce (cpy and
delete previous value) -> do nothing if no index found
*/
void	replace_env_var(char **env, char *target, char *replace)
{
	int	idx;
	char *temp;

	idx = search_env_var(env, target);
	if (idx == -1)
		return;
	temp = env[idx]; 
	env[idx] = ft_strdup(replace);
	free(temp);
	return ;
}
