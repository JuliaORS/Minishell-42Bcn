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

/*
handling redirections for:
handling in/out-file redirect:
-if the command has a valid file descriptor open for inflie, should
redirect the stdin from there
- same logic but for outfile
handling pipes
-if this is not the first command (pos >0 ) it should read from the read-end
of previous command pipe
-if this is not the last command (pos < total_cmd) it should redirect to the 
write-end of the pipe shared with next command
we start with pipes and then file redirect as infile would be duped and prevailed
over the data piped from previous command output (and conversely for outfile)
*/
void	io_redirect(t_proc *pcs, t_exec *exec)
{
	int	pos;

	pos = pcs->pos;
	back_up_stdio(exec , 0);
	if (exec->pipes && pos > 0)
		dup2(exec->pipes[pos - 1][0], STDIN_FILENO);
	if (exec->pipes && pos < exec->total_cmd - 1 && exec->total_cmd > 1)
		dup2(exec->pipes[pos][1], STDOUT_FILENO);
	if (fd_is_open(pcs->fd[0]))
	{
		dup2(pcs->fd[0], STDIN_FILENO);
		close(pcs->fd[0]);
	}
	if (fd_is_open(pcs->fd[1]))
	{
		dup2(pcs->fd[1], STDOUT_FILENO);
		close(pcs->fd[1]);
	}
	return ;
}

/*
function to open the pipes in the parent before dispatching the children
process. take exec object, use the number of comands (nbr of process), 
return noting but update the exec object with an array of initialized pipes.
if n process -> (n - 1) pipes.
each pipe has 2 ends pipe[0, 1] where [0] is read-end and [1] is write end
so for 3 cmds we have pipes[0, 1] = [[0,1],[0,1]] so that : 
cmd0 writes to [0][1] - cmd1 read from [0][1]
cmd1 write to [1][1] - cmd 2 read from [1][0]
*/
void	pipefd_calibrate(t_exec *exec)
{
	int	**pipes;
	int	i;
	int	nb_cmds;

	if (!exec)
		return;
	nb_cmds = (exec)->total_cmd;
	pipes = malloc(sizeof(int) * (nb_cmds - 1));
	if (!pipes)
		error_msg("Out of memory Malloc", ENOMEM, exec, NULL);
	i = 0;
	while (i < nb_cmds - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			error_msg("Out of memory Malloc", ENOMEM, exec, NULL);
		if (pipe(pipes[i]) == -1)
			error_msg("issue while pipe set up", EBADF, exec, NULL);
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
	while (i < exec->total_cmd - 1)
	{
		//printf("closing all pipes in pipes[%i] for total of %i cmd\n", i, exec->total_cmd );
		close(exec->pipes[i][0]);
		close(exec->pipes[i][1]);
		if (exec->pipes[i])
			free(exec->pipes[i]);
		i++;
	}
	free(exec->pipes);
}

/*
if builtins or any function implement a redirection in the parent process
we need to backup and / or restore original STDIN and STDOUT from initial state
*/
void	back_up_stdio(t_exec *exec, int io)
{
	if (!exec)
		return ;
	if (io == 0)
	{
		exec->backup_stdio[0] = dup(STDIN_FILENO);
		exec->backup_stdio[1] = dup(STDOUT_FILENO);
	}
	if (io == 1)
	{
		dup2(exec->backup_stdio[0], STDIN_FILENO);
		close (exec->backup_stdio[0]);
		dup2(exec->backup_stdio[1], STDOUT_FILENO);
		close (exec->backup_stdio[1]);
	}
	return ;
}

int	fd_is_open(int fd)
{
	if (fd > 0)
		return (1);
	return (0);
}