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


#include "../../includes/minishell.h"

void	init_exec(t_exec *exec, t_proc *pcs_chain, char **env)
{
	if (!exec | !pcs_chain)
	{	
		error_msg("init empty struct", 0, exec, pcs_chain);
		return ;
	}
	exec->total_pcs = measure_list(&pcs_chain);
	exec->env = env_dup(env);
	if (!exec->env)
		error_msg("Out of Memory: Environment dup fail", 0, exec, pcs_chain);

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
receive dble pointer to t_proc object. traverse it backward
to first command, then traverse and clean mallocated memory
close all opened fds if any
*/
void	free_chain(t_proc **pcs_chain)
{
	t_proc *chain;

	if (!*pcs_chain)
		return ;
	chain = *pcs_chain;
	while (chain->pos != 0)
		chain = chain->prev;
	while (chain)
	{
		if (chain->arg)
			free_arg(chain->arg);
		if (chain->fd[0] && chain->fd[0] != -1)
			close(chain->fd[0]);
		if (chain->fd[1] && chain->fd[1] != -1)
			close(chain->fd[1]);
		chain = chain->next;
	}
	return ;
}

/*
free NULL-terminated double array of commands arguments
very similar to free_env
*/
void	free_arg(char **arg)
{
	int	i;

	if (!*arg)
		return ;
	i = -1;
	while (arg && arg[++i])
		free(arg[i]);
	if (arg)
		free(arg);
	return ;
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
	if((*exec)->env)
		free_env((*exec)->env);
	if ((*exec)->pids)
		free((*exec)->pids);
	if ((*exec)->pipes)
	{
		close_all_pipes(*exec);
		free((*exec)->pipes);
	}
	if ((*exec)->path)
		free((*exec)->path);
	return ;
}

/*
display error msg, custom error exit number, free memroy
*/
int	error_msg(char *msg, int nb, t_exec *exec, t_proc *pcs)
{
	if (pcs)
	{
		printf("minishell: %s: %s\n", pcs->arg[0], msg);
		free_chain(&pcs);
		
	}
	else
		printf("minishell: %s\n", msg);
	if (exec)
		free_exec(&exec);
	if (nb)
		exit(nb);
	else
		exit(EXIT_FAILURE);
}