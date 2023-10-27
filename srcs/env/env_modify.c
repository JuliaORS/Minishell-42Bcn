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

int	shlvl_update(int shlvl_);

/*
increase the memory size of env array by one char * and copy it while freeing up
the memory used from the source
*/
char	**realloc_env(char **env, char *var)
{
	char	**new_env;
	int		i;
	int		size;

	size = count_var_env(env) + 1;
	new_env = ft_calloc(size + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env && i < size - 1)
	{
		new_env[i] = ft_strdup(env[i]);
		free_pntr(env[i]);
		i++;
	}
	new_env[size] = NULL;
	new_env[size - 1] = ft_strdup(var);
	free_pntr(env);
	return (new_env);
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
	return (new_env);
}

/*
search for a target in the env, found it's index and repalce (cpy and
delete previous value) -> do nothing if no index found
*/
void	replace_env_var(char **env, char *target, char *replace)
{
	int		idx;
	char	*temp;

	idx = search_env_var(env, target);
	if (idx == -1)
		return ;
	temp = env[idx];
	env[idx] = ft_strdup(replace);
	free(temp);
	return ;
}

/*
get the SHLVL from env copied from shell and add 1 to it
- combined key_val_ manopulatio and atoi -> itoa to add 1
- carefull with variable and free on ft_strjoin to avoid leak of SF
- idx and tmp passed as arguments because of norminette rules of 4 variables max
*/
int	shlvl_add(t_exec *exec, int idx, char *tmp, char *tmp_join)
{
	char	**temp;
	int		shl_vl;

	tmp_join = extract_variable("SHLVL=");
	idx = search_env_var(exec->env, tmp_join);
	free_pntr(tmp_join);
	if (idx == -1)
		return (export_exec(exec, "SHLVL=1", 1));
	temp = key_val_pair(exec->env[idx]);
	shl_vl = ft_atoi(temp[1]);
	shl_vl = shlvl_update(shl_vl);
	free_pntr(temp[1]);
	temp[1] = ft_itoa(shl_vl);
	tmp_join = ft_strjoin(temp[0], "=");
	if (tmp_join)
	{
		tmp = ft_strjoin(tmp_join, temp[1]);
		free_pntr(tmp_join);
	}
	free_key_val(temp);
	if (!tmp)
		return (0);
	export_exec(exec, tmp, 1);
	free_pntr(tmp);
	return (1);
}

int	shlvl_update(int shlvl_)
{
	if (shlvl_ < 0)
		shlvl_ = 0;
	else
		shlvl_++;
	if (shlvl_ > 1000)
	{
		ft_printf(STDERR_FILENO, "minishell: warning: shell level (%i)"
			" too high, resetting to 1\n", shlvl_);
		shlvl_ = 1;
	}
	return (shlvl_);
}
