/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:04:39 by rjobert           #+#    #+#             */
/*   Updated: 2023/09/28 11:31:43 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_input(int	input_fd)
{
	if (dup2(input_fd, STDIN_FILENO) == -1)
		return ; // later on treat here exit case and clean mem
}

void	redirect_output(int output_fd)
{
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		return ; // same as above
}

/*
function to open the pipes in the parent before dispatching the children
process. take exec object, use the number of comands (nbr of process), 
return noting but update the exec object with an array of initialized pipes.
if n process -> (n - 1) pipes -> (n - 1) * 2 fd pointing to mem buffer and 
not to open file tble.
*/
void	pipefd_calibrate(t_exec **exec)
{
	int	*pipes;
	int	i;
	int	nb_cmds;

	if (*exec)
		return;
	nb_cmds = (*exec)->total_pcs;
	pipes = malloc(sizeof(int) * (nb_cmds - 1) * 2);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < nb_cmds - 1)
	{
		if (pipe(pipes + (2 * i) )== -1)
			exit(EXIT_FAILURE);
		i++;
	}
	(*exec)->pipes = pipes;
}

/*
closing all pipes as per their fd stored in exec object.
if we have n process, we have n - 1 pipes, so we have (n - 1) * 2 nber of fd
*/
void	close_all_pipes(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < (exec->total_pcs - 1) * 2)
	{
		close(exec->pipes[i]);
		i++;
	}
}