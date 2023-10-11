/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:12:32 by rjobert           #+#    #+#             */
/*   Updated: 2023/09/20 21:12:35 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	init_exec(t_exec *exec, char **env)
{
	if (!exec)
	{	
		error_msg("init empty struct", 0, exec, NULL);
		return ;
	}
	exec->env = env_dup(env, 0, 0); 
	if (!exec->env)
		error_msg(MALLOC_MESS, 0, exec, NULL);
	exec->dir_init = 0;
	exec->pids = NULL;
	exec->pipes = NULL;
	exec->path = NULL;
}

int	measure_list(t_proc **list)
{
	int		n;
	t_proc *lst;

	n = 0;
	if (!*list)
		return (n);
	lst = *list;
	while (lst)
	{
		n++;
		lst = lst->next;
	}
	return (n);
}

/*
free all the mallocated element of the t_exec object
close all fds opened by pipes in parents and still
open in the process (dbled in Vnode)
*/
void	free_exec(t_exec **exec)
{
	if (!*exec)
		return ;
	// if((*exec)->env)    
	// 	free_env((*exec)->env);
	if ((*exec)->pids)
	{
		free((*exec)->pids);
		(*exec)->pids = NULL;
	}
	if ((*exec)->pipes)
	{
		close_all_pipes(*exec);
		(*exec)->pipes = NULL;
	}
	if ((*exec)->path)
	{
		free((*exec)->path);
		(*exec)->path = NULL;
	}
	return ;
}

/*
display error msg, custom error exit number, free memry
*/
int	error_msg(char *msg, int nb, t_exec *exec, t_proc *pcs)
{
	if (pcs)
		printf("minishell: %s: %s\n", pcs->arg[0], msg);
	else
		printf("minishell: %s\n", msg);
	if (exec)
		free_exec(&exec);
	if (exec->total_cmd == 1 && is_builtin(pcs))
		return (nb);
	if (nb)
		exit(nb);
	else
		exit(EXIT_FAILURE);
}

void	free_split(char ***split_result)
{
	int	i;

	if (!*split_result || !split_result)
		return ;
	i = 0;
	while ((*split_result)[i])
	{
		free((*split_result)[i]);
		i++;
	}
	free(*split_result);
	*split_result = NULL;
}