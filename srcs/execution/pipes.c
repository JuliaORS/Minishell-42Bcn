/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:04:39 by rjobert           #+#    #+#             */
/*   Updated: 2023/09/20 21:04:41 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"
#include <string.h>
#include <errno.h>

void	redirect_input(int	input_fd)
{
	if (dup2(input_fd, STDIN_FILENO) == -1)
	{
		//printf("\n process with bugs fd input is %i and duped is %i\n", input_fd, STDIN_FILENO);
		//printf("\n process with bugs is %i\n", exec_trgt->pos);
		//perror("what is the issue");
		//printf("bug is %s\n",strerror(errno));
		//error_msg("dup2 input: bad file descriptor", EBADF, NULL, NULL); //return ;
		return;
	}
	return ; // later on treat here exit case and clean mem
}

void	redirect_output(int output_fd)
{
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		error_msg("dup2 output: bad file descriptor", EBADF, NULL, NULL);
	return ;
}

/*
function to open the pipes in the parent before dispatching the children
process. take exec object, use the number of comands (nbr of process), 
return noting but update the exec object with an array of initialized pipes.
if n process -> (n - 1) pipes -> (n - 1) * 2 fd pointing to mem buffer and 
not to open file tble.
*/
void	pipefd_calibrate(t_exec *exec)
{
	int	*pipes;
	int	i;
	int	nb_cmds;

	if (!exec)
		return;
	nb_cmds = (exec)->total_pcs;
	pipes = malloc(sizeof(int) * (nb_cmds - 1) * 2);
	if (!pipes)
		return ;
	i = 0;
	while (i < nb_cmds - 1)
	{
		if (pipe(pipes + (2 * i) )== -1)
			exit(EXIT_FAILURE);
		i++;
	}
	(exec)->pipes = pipes;
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