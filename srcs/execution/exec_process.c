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

int	exec_machine(t_proc *pcs_chain, t_exec *exec)
{
	if (!pcs_chain)
		return (0);
	if (exec->total_cmd == 1 && is_builtin(pcs_chain))
	{
		exec->in_parent = 1;
		exec->exit[0] = exec_builtin(pcs_chain, exec);
		back_up_stdio(exec, 1);
		free_exec(&exec);
		return (exec->exit[0]);
	}
	exec->in_parent = 0;
	pipefd_calibrate(exec);
	launch_process(exec, &pcs_chain);
	close_all_pipes(exec);
	wait_processes(exec);
	free_exec(&exec);
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
	else if (!ft_strncmp(cmd, "exit", 5))
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
	else if (!ft_strncmp(cmd, "exit", 5))
		return (ft_exit(exec, pcs_chain->arg));
	printf("minishell: %s: not a valid option\n", pcs_chain->arg[0]);
	return (1);
}

/*
special error function for builtin execution in parent process
to not exit
*/
int	error_builtin(char *msg, int nb, t_exec *exec, char *bltn)
{
	if (bltn)
		printf("minishell: %s: %s\n", msg, bltn);
	else
		printf("minishell: %s\n", msg);
	if (exec)
		free_exec(&exec);
	return (nb);
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
and in that case iterating or env wasn't a clear succees, so we apply execve 
with arg_cmd[0] as path
3 - if nothing worked, command is clearly unknown -> exit error message  
*/
void	exec_bash(t_proc **exec_trgt, t_exec **exec)
{
	if (access((*exec)->path, F_OK) == 0)
	{
		if (access((*exec)->path, X_OK) != 0)
		{
			error_msg(NOPERM_MESS, NOPERM, *exec, *exec_trgt);
		}
		if (execve((*exec)->path, (*exec_trgt)->arg, (*exec)->env) == -1)
			exit(EXIT_FAILURE);
	}
	if (ft_strchr((*exec_trgt)->arg[0], '/') && access((*exec_trgt)->arg[0], F_OK) == 0) //SPECIAL CASE ABSOLUTE / RELATIVE PATH
	{
		if (execve((*exec_trgt)->arg[0], (*exec_trgt)->arg, (*exec)->env) == -1)
			exit(EXIT_FAILURE);
	}
	error_msg(CMNF_MESS, CMNOFOUND, *exec, *exec_trgt);
}