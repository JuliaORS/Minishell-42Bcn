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

int	exec_machine(t_proc *pcs_chain, char *env[])
{
	t_exec	exec;
	// t_proc *chain;
	
 	// chain = pcs_chain;
	// while(chain)
 	// {
 	// 	printf("process position is  %i\n", chain->pos);
 	// 	printf("	command is %s and flag is %s \n", chain->arg[0], chain->arg[1]);
 	// 	printf("	fd inputs is %i and output is %i\n", chain->fd[0], chain->fd[1]);
 	// 	printf("\n");
 	// 	chain = chain->next;
 	// }
	// int i = -1;
	// while (env && env[++i])
	// 	printf("env var is : %s\n", env[i]);
	if (!pcs_chain)
		return (0);
	init_exec(&exec, pcs_chain, env);
	if (exec.total_cmd == 1 && is_builtin(pcs_chain))
		return (exec_builtin(pcs_chain, &exec));
	pipefd_calibrate(&exec);
	launch_process(&exec, &pcs_chain);
	close_all_pipes(&exec);
	wait_processes(&exec);
	// ADD A CLEAN EXEC & PIDS
	return (EXIT_SUCCESS);
}


int	is_builtin(t_proc*pcs_chain)
{
	char	*cmd;
	
	if (!pcs_chain || !pcs_chain->arg)
		return (0);
	cmd = pcs_chain->arg[0];
	if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	else if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	else if (!ft_strncmp(cmd, "env", 5))
		return (1);
	else if (!ft_strncmp(cmd, "export", 7))
		return (1);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	return (0);
}

int	exec_builtin(t_proc *pcs_chain, t_exec *exec)
{
	char	*cmd;
	if (!pcs_chain)
		return (1);
	cmd = pcs_chain->arg[0];
	io_redirect(pcs_chain, exec);
	if (!ft_strncmp(cmd, "cd", 3))
		return (ft_cd(exec, pcs_chain->arg));
	else if (!ft_strncmp(cmd, "pwd", 4))
		return(ft_pwd(exec, pcs_chain->arg));
	else if (!ft_strncmp(cmd, "echo", 5))
		return(ft_echo(exec, pcs_chain->arg));
	else if (!ft_strncmp(cmd, "env", 5))
		return(ft_env(exec, pcs_chain->arg));
	else if (!ft_strncmp(cmd, "export", 7))
		return (ft_export(exec, pcs_chain->arg));
	else if (!ft_strncmp(cmd, "unset", 6))
		return (ft_unset(exec, pcs_chain->arg));
	printf("minishell: %s: not a valid option\n", pcs_chain->arg[0]);
	return (1);
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

/* 
now let's look for a command line function in the path and 
return the path exec 
 1 - we iterate over all path (if there are some) and
 use strjoin to to first go from cmd (like cat) to a
 cmd path (like /cat) and use strjoin again on a potential path
 2 - we free free the path_cmd and we now use the access function 
 to check if path/cmd  (like /bin/cat) exist with F_OK. 
 3 - if it does, we return (and free in another function) else
 we free and move to next potential from in all_path 
 */
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
			error_msg("Permission denied", NOPERM, *exec, *exec_trgt);
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
	error_msg("command not found", CMNOFOUND, *exec, *exec_trgt);
}