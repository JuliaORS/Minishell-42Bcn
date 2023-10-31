/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_env_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:50:52 by rjobert           #+#    #+#             */
/*   Updated: 2023/10/24 19:50:54 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
Creates an export environment (exp_env) by iterating over the provided 
environment (env). For each variable in env, it adds the variable to the 
exp_env using add_expenv. Returns the exp_env
*/
t_xpenv	*create_xp_env(char **env)
{
	int		i;
	t_xpenv	*exp_env;

	if (!*env)
		return (NULL);
	i = 0;
	exp_env = NULL;
	while (env && env[i])
	{
		add_expenv(&exp_env, env[i], 1);
		i++;
	}
	return (exp_env);
}

/*
Frees the entire export environment list.
Iterates through each node in the list, frees the variable, and then the node 
itself.
*/
void	free_xpenv(t_xpenv	**list)
{
	t_xpenv	*tmp;
	t_xpenv	*head;

	if (!*list)
		return ;
	head = *list;
	while (head)
	{
		tmp = head->next;
		free_pntr(head->var);
		free_pntr(head);
		head = tmp;
	}
	*list = NULL;
}

/*
Deletes a specific node in the export environment list that matches the 
provided env string.
If the node to delete is found, it updates the next pointers, frees the 
variable, and then the node itself.
*/
void	delete_node_xpenv(t_xpenv **head_ref, char *env, t_xpenv *prev)
{
	t_xpenv	*temp;
	char	*tmp;

	temp = *head_ref;
	while (temp)
	{
		if (ft_strrchr(temp->var, '='))
			tmp = extract_variable(temp->var);
		else
			tmp = ft_strdup(temp->var);
		if (!ft_strncmp(env, tmp, ft_strlen(env) + 1))
		{
			if (prev)
				prev->next = temp->next;
			else
				*head_ref = temp->next;
			free_pntr(temp->var);
			free_pntr(temp);
			free_pntr(tmp);
			return ;
		}
		prev = temp;
		temp = temp->next;
		free_pntr(tmp);
	}
}
