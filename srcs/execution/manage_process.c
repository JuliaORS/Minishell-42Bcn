/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:17:44 by rjobert           #+#    #+#             */
/*   Updated: 2023/09/21 19:17:47 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/*
wait for each process to finish, starting by the last one - to make sure
all commands execute correctly
*/
void	wait_processes(t_exec *exec)
{
	pid_t	wpid;
	int		status;
	int		total_cmd;

   total_cmd = exec->total_pcs - 1;
	while (total_cmd >= 0)
	{
		wpid = waitpid(exec->pids[total_cmd], &status, 0);
		total_cmd--;
	}
}

/*
launch as many processes as there are command to execute separated
by pipes.
malloc an array of pids. exit if fails
iterate over a loop for the total nber of process. fork() fails quit,
otherwise :
- if child process -> execute the command : we pass the entire
chain if need information from previous command, inidate which node is 
the command to execute.
- if parent : add the pids to array. in the end add the whole array to
exec object.
*/
void	launch_process(t_exec *exec, t_proc **pcs_chain)
{
	int		i;
	pid_t	pid;
	pid_t	*pids;

	if (!exec || !*pcs_chain)
		return ; //extra clean exit later on
	pids = malloc(sizeof(pid_t) * (exec)->total_pcs);
	if (!pids)
		return ; //extra clean exit later on
	(exec)->pids = pids;
	//printf("there is an env and it is : %s \n", exec->env[2]);
	i = 0;
	while (i < (exec)->total_pcs && *pcs_chain)
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE); // special case : clean all that was allocated
		if (pid == 0)
			command_process(pcs_chain, &exec, i);
		if (pid > 0)
			exec->pids[i] = pid;
		i++;
	}
	return ;
}
/*
we first check no empty data structure, then traverse to the node
being our execution target.
- if this is the first node and a file descriptor is open (due to a 
< caught during parsing and valid file) : we redirect the stdin
to this fd. if there is a following command, we redirect stdout to 
the corresponding pipe (pipe[1]) -> see for pipe sync. we then close the 
fd.
- if this is the last command (position == nb_cmmd - 1 bcause of array pos):
if there is a fd for output and we redirect out to it. fi there were a cmd
before (and therefore a pipe) - we redirect stdin with it
- if neither first nor last command, it is a middle one and therefore
stdin redirect to read of previous pipe and stdout redirect to write 
of next pipe. arithmetic explained outside of this program
- we then close all pipes to avoid hanging pipes
- execute the command
*/
void	command_process(t_proc **pcs_chain, t_exec **exec, int pos)
{
	t_proc	*exec_trgt;
	int i;

	if (!*pcs_chain)
		return ;
	exec_trgt = *pcs_chain;
	i = 0;
	while (i != pos)
	{
		exec_trgt = exec_trgt->next;
		i++;
	}
	if (exec_trgt->pos == 0)
		first_process(exec_trgt, exec);
	if (exec_trgt->pos == (*exec)->total_pcs - 1)
		last_process(exec_trgt, exec);
	else
		mid_process(exec_trgt, exec);
	close_all_pipes(*exec);
	build_execve(&exec_trgt, exec);
	perror("execve failed"); // Print an error message
    exit(EXIT_FAILURE);
}

/*
heart of the execution machine. 
objective : we build the execve with error check along the way
inputs for execve are path (/bin/cat), an array of command info
 (ex : "ls -l" would yield {"ls, "-l", NULL}) and the env variables. 
 1- receive the array arg_cmd from parsing ({cmd, arguments, NULL}): 
 2 - we use search_path to look for the path inside the env[] and return a
 splitmatrix of all path separated by ':' as in LINUX environment
 3 - we search for the correct path inside the matrix with exec_path : if access
 function return a path, it is where the cmd can be found,
 otherxise return null. we will need to free afterward as we used malloc
 3.b - special case when the cmd is with absolute path
 (instead of cat user entered /bin/cat) in that case the path is already here,
 so if arg_user[0] = '/', path = arg_user (i.e. arg_cmd[0])
 3.c - special case if we have relative path (like ./script.sh) in that case
 the execve function needs arguments to be clean for special cases so we 
 apply the function relative_path_clean()
 4 - we can clean our path matrix, and free the cmplete_path after using
 execve_bash : an application of execve with special error handling
 */
void	build_execve(t_proc **exec_trgt, t_exec **exec)
{
	char	**env_paths;

	if (!*exec_trgt)
		return ;
	env_paths = search_path((*exec)->env);
	if ((*exec_trgt)->arg[0][0] == '/') //absolute path handled here but no relative path
		(*exec)->path = (*exec_trgt)->arg[0];
	else
		(*exec)->path = exec_path(env_paths, *exec_trgt);
	//special case of relative path not handled 
	exec_bash(exec_trgt, exec);
	//free_split(env_path); to do later

}

void	first_process(t_proc *exec_trgt, t_exec **exec)
{
	if (!exec_trgt || !*exec)
		return ;
	if (exec_trgt->fd[0] == -1 || exec_trgt->fd[1] == -1)
		error_msg("bad file descriptor", EBADF, *exec, exec_trgt);
	if (exec_trgt->fd[0]) // if infile redirect < 
	{
		redirect_input(exec_trgt->fd[0]);
		close(exec_trgt->fd[0]);
	}
	if (exec_trgt->fd[1]) // if outfile redirect >
	{
		redirect_output(exec_trgt->fd[1]);
		close(exec_trgt->fd[1]);
	}
	if (exec_trgt->next != NULL)
		redirect_output((*exec)->pipes[1]);
}

void	last_process(t_proc *exec_trgt, t_exec **exec)
{
	if (!exec_trgt || !*exec)
		return ;
	if (exec_trgt->fd[0] == -1 || exec_trgt->fd[1] == -1)
		error_msg("bad file descriptor", EBADF, *exec, exec_trgt);
	if (exec_trgt->fd[0]) // if infile redirect < 
	{
		redirect_input(exec_trgt->fd[0]);
		close(exec_trgt->fd[0]);
	}
	else if (exec_trgt->prev != NULL) // if no infile redirection and prev command we pipe
		redirect_input((*exec)->pipes[(exec_trgt->pos - 1) * 2]);
	if (exec_trgt->fd[1]) // if outfile redirect >
	{
		redirect_output(exec_trgt->fd[1]);
		close(exec_trgt->fd[1]);
	}
}

void	mid_process(t_proc *exec_trgt, t_exec **exec)
{
	if (exec_trgt->fd[0] == -1 || exec_trgt->fd[1] == -1)
		error_msg("bad file descriptor", EBADF, *exec, exec_trgt);
	if (exec_trgt->fd[0])
	{
		redirect_input(exec_trgt->fd[0]);
		close(exec_trgt->fd[0]);
	}
	else
		redirect_input((*exec)->pipes[(exec_trgt->pos - 1) * 2]);
	if (exec_trgt->fd[1])
	{
		redirect_output(exec_trgt->fd[1]);
		close(exec_trgt->fd[1]);
	}
	else
		redirect_output((*exec)->pipes[(exec_trgt->pos) * 2 + 1]);
	}