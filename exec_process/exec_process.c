/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:20:02 by rjobert           #+#    #+#             */
/*   Updated: 2023/09/28 11:31:56 by julolle-         ###   ########.fr       */
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

   total_cmd = exec->total_pcs;
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
void	launch_process(t_exec **exec, t_proc **pcs_chain)
{
	int		i;
	pid_t	pid;
	pid_t	*pids;

	if (!*exec || !*pcs_chain)
		return ; //extra clean exit later on
	pids = malloc(sizeof(pid_t) * (*exec)->total_pcs);
	if (!pids)
		return (NULL); //extra clean exit later on
	i = 0;
	while (i < (*exec)->total_pcs && *pcs_chain)
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE); // special case : clean all that was allocated
		if (pid == 0)
			command_process(pcs_chain, exec, i);
		if (pid > 0)
			pids[i] = pid;
		i++;
	}
	(*exec)->pids = pids;
	return ;
}
/*
we first check no empty data structure, then traverse to then node
being our execution target.
- if this is the first node and a file descriptor is open (due to a 
< caught during parsing and valid file) : we redirect the input (stdin)
to this fd. if there is a following command, we redirect output (stdout)
to the corresponding piep (pipe[1]) -> see for pipe sync. we then close the 
fd.
- if this is the last command (position == nb_cmmd - 1 bcause of array pos):
if there is a fd for output and we redirect out to it. fi there were a cmd
before (and therefore a pipe) - we redirect stdin with it
- if neither first nor last command, it is a middle one and therefore
stdin redirect to read of previous pipe and stdout redirect to write 
of next pipe. arithmetic explained outside of this program
- we then close all pipes to avoid hanging pipes
- execute the command
WARNING : REDIRECTION NOT DONE :
	- if > fd[1] in first command
	- if < fd[0] or > fd[1] in mid command
	- if < fd[0] in last command
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
		exec_trgt = exec_trgt->next;
	if (exec_trgt->position == 0)
	{
		if (exec_trgt->fd[0])
		{
			redirect_input(exec_trgt->fd[0]);
			close(exec_trgt->fd[0]);
		}
		if (exec_trgt->next != NULL)
			redirect_output((*exec)->pipes[1]);
	}
	else if (exec_trgt->position == (*exec)->total_pcs - 1) 
	{
		if (exec_trgt->fd[1])
		{
			redirect_output((*exec)->pipes[(exec_trgt->position) * 2 + 1]);
			close(exec_trgt->fd[1]);
		}
		if (exec_trgt->prev != NULL)
			redirect_input((*exec)->pipes[(exec_trgt->position - 1) * 2]);
	}
	else
	{
		redirect_input((*exec)->pipes[(exec_trgt->position - 1) * 2]);
		redirect_output((*exec)->pipes[(exec_trgt->position) * 2 + 1]);
	}
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
 execve_bash : an application of execve with special error handling*/
void	build_execve(t_proc **exec_trgt, t_exec **exec)
{
	char	**env_paths;
	char	*valid_path;

	if (!*exec_trgt)
		return ;
	env_paths = get_env((*exec)->env); // Minishell doesn't have any so far : how do we do ? otherwise search_path like in pipex
	(*exec)->path = exec_path(env_paths, *exec_trgt);
	//special case of relative path not handled 

	execve_bash(t_proc **exec_trgt, t_exec **exec);
	//free_split(env_path); to do later

}

/* now let's look for a command line function in the path and 
return the path exec 
 1 - we iterate over all path (if there are some) and
 use strjoin to to first go from cmd (like cat) to a
 cmd path (like /cat) and use strjoin again on a potential path
 2 - we free free the path_cmd and we now use the access function 
 to check if path/cmd  (like /bin/cat) exist with F_OK. 
 3 - if it does, we return (and free in another function) else
 we free and move to next potential from in all_path */
char	*exec_path(char **all_path, t_proc *exec_trgt)
{
	char	*test_path;
	char	*temp_cmd;
	char	*cmd;

	if (!all_path)
		return (NULL);
	cmd = exec_trgt->arg[0];
	while (*all_path)
	{
		temp_cmd = ft_strjoin("/", cmd);
		test_path = ft_strjoin(*all_path, temp_cmd);
		free(temp_cmd);
		if (access(test_path, F_OK) == 0)
			return (test_path);
		free(test_path);
		all_path++;
	}
	return (NULL);
}

/* 
Objective : apply execve with many error handling
1 - first if the path is findable (the path reach a file that exist - 
we verify that (again) with access and F_OK) we then test several cases:
1.a - if the file is not exectutable ( a script.sh where -x- right are
not for user or group -> we return error 126 and exit message)
1.b - else we can apply execve and return the error message if issue
2 - if the path is not ok but arg_cmd[0] contains a "/" it is possible
that our command is a relative path with directory like subdir/scripth.sh
and in that case iterating or env wasn't a clear sucees, so we apply execve 
with arg_cmd[0] as path
3 - if nothing worked, command is clearly unknown -> exit error message  
*/
<<<<<<< HEAD
void	exec_bash(t_proc **exec_trgt, t_exec **exec)
=======
void	execve_bash(t_proc **exec_trgt, t_exec **exec)
>>>>>>> origin/exec_process_branch
{
	if (access((*exec)->path, F_OK) == 0)
	{
		if (access((*exec)->path, X_OK) != 0)
<<<<<<< HEAD
			exit(EXIT_FAILURE);
			//exit_error(126, strerror(errno), (*exec_trgt)->args[0], p_cmd);
		if (execve((*exec)->path, (*exec_trgt)->arg, (*exec)->env) == -1)
			exit(EXIT_FAILURE);
			//exit_error(errno, strerror(errno), (*p_cmd)->args[0], p_cmd);
	}
	if (ft_strchr((*exec_trgt)->arg[0], '/') && access((*exec_trgt)->arg[0], F_OK) == 0) //SPECIAL CASE ABSOLUTE / RELATIVE PATH
	{
		if (execve((*exec_trgt)->arg[0], (*exec_trgt)->arg, (*exec)->env) == -1)
			exit(EXIT_FAILURE);
			//exit_error(errno, strerror(errno), (*p_cmd)->args[0], p_cmd);
	}
	exit(EXIT_FAILURE);
	//exit_error(127, "command not found", (*exec_trgt)->arg[0], p_cmd);
}
=======
			//exit_error(126, strerror(errno), (*exec_trgt)->args[0], p_cmd);
		if (execve((*exec)->path, (*exec_trgt)->arg, (*exec)->env) == -1)
			//exit_error(errno, strerror(errno), (*p_cmd)->args[0], p_cmd);
	}
	// if (ft_strchr((*p_cmd)->args[0], '/') 
	// 	&& access((*p_cmd)->args[0], F_OK) == 0) SPECIAL CASE RELATIVE PATH
	{
		if (execve((*exec_trgt)->arg[0], (*exec_trgt)->arg, (*exec)->env) == -1)
			//exit_error(errno, strerror(errno), (*p_cmd)->args[0], p_cmd);
	}
	exit_error(127, "command not found", (*exec_trgt)->arg[0], p_cmd);
}
>>>>>>> origin/exec_process_branch
