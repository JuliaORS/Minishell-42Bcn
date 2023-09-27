/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:20:02 by rjobert           #+#    #+#             */
/*   Updated: 2023/09/20 21:20:04 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

int	exec_machine(t_proc *pcs_chain, char *env[])
{
	t_exec	exec;
	t_proc	*chain;
	
	if (!pcs_chain)
		return (0);
	
	init_exec(&exec, pcs_chain, env); // to replace with a getenv
	pipefd_calibrate(&exec); //open as many pipes as needed 
	launch_process(&exec, &pcs_chain); // fork all the process from cmds, hack input out put if any
	close_all_pipes(&exec); //closing al the pipes open on father side
	wait_processes(&exec);  // wait for the execution of all children
	 
	exit(EXIT_SUCCESS);
}

/*
 Extract the PATH from environment variables in env[]
 1 - we receive env from the command line, it is array of char*
 if it is null (env empty), we return a matrix split of a default path
 2 - else we itetrate over each env[x] while not null, iterate while first
 four chars are different than "PATH"
 3 - when we found it, we return it minus the 5 first char (that are "PATH=")
 4 - if there an is no path in the env (extremely rare but this is 42 school...)
 we replace it by a pre-define PATH in the header
*/
char	**search_path(char *env[])
{
	int		i;
	char	**path_matrix;
	char	*path;

	path = NULL;
	i = 0;
	if (!env || !*env)
		return (NULL) ; //Careful this is pipex modified for no environment
	else
	{
		while (env[i] && ft_strncmp(env[i], "PATH", 4))
			i++;
		if (env[i])
			path = env[i] + 5;
	}
	path_matrix = ft_split(path, ':');
	return (path_matrix);
}

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
void	exec_bash(t_proc **exec_trgt, t_exec **exec)
{
	if (access((*exec)->path, F_OK) == 0)
	{
		if (access((*exec)->path, X_OK) != 0)
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
