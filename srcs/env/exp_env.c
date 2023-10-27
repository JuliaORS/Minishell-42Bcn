/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:37:46 by rjobert           #+#    #+#             */
/*   Updated: 2023/10/24 15:37:49 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exp_env_format(char *env, int type);

t_xpenv *node_exp_env(char *env, int type)
{
	t_xpenv	*exp_env;

	if (!env)
		return (NULL);
	exp_env = malloc(sizeof(t_xpenv));
	if (!exp_env)
		return (NULL);
	exp_env->next = NULL;
	exp_env->type = type;
	exp_env->var = exp_env_format(env, type);
	return (exp_env);
}

char	*exp_env_format(char *env, int type)
{
	char	*value;
	char	*temp_var;
	char	*temp_val;

	if (type == 0)
		temp_var = ft_strdup(env);
	else
	{
		temp_var = extract_variable(env);
		temp_val = extract_value(env);
		value = ft_strjoin(temp_var, "=");
		free(temp_var);
		temp_var = ft_strjoin("\"", temp_val);
		free(temp_val);
		temp_val = ft_strjoin(temp_var,"\"");
		free(temp_var);
		temp_var = ft_strjoin(value, temp_val);
		free(temp_val);
		free(value);
	}
	return (temp_var);
}

int	search_n_replace(t_xpenv *head, char *env, int type)
{
	char *temp_node;
	char *temp;

	if (type == 0)
		temp = ft_strdup(env);
	else
		temp = extract_variable(env);
	while (head)
	{
		if (head->type == 0)
			temp_node = ft_strdup(head->var);
		else
			temp_node = extract_variable(head->var);
		if (!ft_strncmp(temp, temp_node, ft_strlen(temp)))
		{
			free(head->var);
			head->var = exp_env_format(env, type);
			free(temp_node);
			free(temp);
			return (1);
		}
		free(temp_node);
		head = head->next;
	}
	free(temp);
	return (0);
}

void	add_expenv(t_xpenv **xpenv, char *env, int type)
{
	t_xpenv *node;
	t_xpenv *head;

	node = node_exp_env(env, type);
	if (!node)
		return ;
	if (!*xpenv)
	{
		*xpenv = node;
		return ;
	}
	head = *xpenv;
	if (search_n_replace(head, env, type) == 1)
	{
		free_pntr(node->var);
		free(node);
		return;
	}
	while(head)
	{
		if (!head->next)
			break;
		head = head->next;
	}
	head->next = node;
}
