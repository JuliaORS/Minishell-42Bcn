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
