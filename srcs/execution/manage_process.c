/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:17:44 by rjobert           #+#    #+#             */
/*   Updated: 2023/10/14 13:19:13 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	close_cmd_fd(t_proc *pcs);
/*
wait for each process to finish, starting by the last one - to make sure
all commands execute correctly
*/
void	wait_processes(t_exec *exec)
{
	pid_t	wpid;
	int		status;
	int		total_cmd;
	int		signal;

   	total_cmd = exec->total_cmd - 1;
	while (total_cmd >= 0)
	{
		wpid = waitpid(0, &status, 0);
		if (wpid == exec->pids[exec->total_cmd - 1])
		{
			if (WIFEXITED(status))
				exec->exit[0] = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				signal = WTERMSIG(status);
				if (signal == SIGINT)
					exec->exit[0] = 130;
				else if (signal == SIGQUIT)
					exec->exit[0] = 131;
			}
		}
		total_cmd--;
	}
}

/*
launch as many processes as there are command to execute separated
by pipes.
malloc an array of pids. exit if fails
iterate over a loop for the total nber of process. fork() fails quit,
otherwise :
- if child process -> execute the command : we pass the node with data
- if parent : add the pids to array. in the end add the whole array to
exec object.
*/
void	launch_process(t_exec *exec, t_proc **pcs_chain)
{
	int		i;
	pid_t	pid;
	t_proc	*pcs;

	if (!exec || !*pcs_chain)
		return ;
	(exec)->pids = malloc(sizeof(pid_t) * (exec)->total_cmd);
	if (!(exec)->pids)
		error_msg(MALLOC_MESS, ENOMEM, exec, NULL);
	pcs = *pcs_chain;
	i = 0;
	init_signals(EXEC);
	while (i < exec->total_cmd && pcs)
	{
		pid = fork();
		if (pid == -1)
			error_msg("fork failed", ENOMEM, exec, NULL);
		if (pid == 0)
			command_process(pcs, exec);
		if (pid > 0)
			exec->pids[i] = pid;
		close_cmd_fd(pcs);
		pcs = pcs->next;
		i++;
	}
}

/*
we first check no empty data structure.
- if file descriptor issues at parsing -> display error and clean exit
- handle redirection as indicated in the linked-list of commands
- we then close all pipes to avoid hanging pipes
- execute the command ; if builtin appy our functions, otherwise execve
*/
void	command_process(t_proc *pcs, t_exec *exec)
{
	if (!pcs || !pcs->arg[0])
		return ;
	check_io_fd(pcs, exec);
	io_redirect(pcs, exec);
	close_all_pipes(exec);
	if (is_builtin(pcs))
	{
		exec->exit[0] = exec_builtin(pcs, exec);
		exit(exec->exit[0]);
	}
	else
		build_execve(&pcs, &exec);
}

/*
heart of the execution machine. 
objective : we build the execve with error check along the way.
Inputs for execve are exec path (/bin/cat), an array of command info
 (ex : "ls -l" would yield {"ls, "-l", NULL}) and the env variables. 
 1- receive the array arg in t_proc from parsing ({cmd, arguments, NULL}): 
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
	int		relative_path;

	if (!*exec_trgt || !(*exec_trgt)->arg)
		return ;
	relative_path = 0;
	env_paths = search_path((*exec)->env);
	if (env_paths == NULL)
	{
		if (execve((*exec_trgt)->arg[0], (*exec_trgt)->arg, (*exec)->env) == -1)
			error_msg("No such file or directory", CMNOFOUND, *exec, *exec_trgt);
	}
	if ((*exec_trgt)->arg[0][0] == '/' || ((*exec_trgt)->arg[0][0] == '.' && 
		(*exec_trgt)->arg[0][1] == '/'))
		{
			(*exec)->path = (*exec_trgt)->arg[0];
			relative_path = 1;
		}
	else
		(*exec)->path = exec_path(env_paths, *exec_trgt);
	if (relative_path == 1)
		relative_path_clean(exec_trgt, exec);
	exec_bash(exec_trgt, exec);
	free_split(&env_paths);
}

/*
quick utils to close fds from infile outfile in parents
to avoid duplicate  with children or fd leaks later on
*/
void	close_cmd_fd(t_proc *pcs)
{
		if (fd_is_open(pcs->fd[0]))
			close(pcs->fd[0]);
		if (fd_is_open(pcs->fd[1]))
			close(pcs->fd[1]);
}
