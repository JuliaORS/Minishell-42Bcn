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

	// chain = pcs_chain; 
	// while(chain)
 	// {
 	// 	printf("process position is  %i\n", chain->pos);
 	// 	printf("	command is %s and flag is %s \n", chain->arg[0], chain->arg[1]);
 	// 	printf("	fd inputs is %i and output is %i\n", chain->fd[0], chain->fd[1]);
 	// 	printf("\n");
 	// 	chain = chain->next;
 	// }
	if (!pcs_chain)
		return (0);
	if (exec->total_cmd == 1 && is_builtin(pcs_chain))
	{
		exec->exit = exec_builtin(pcs_chain, exec);
		back_up_stdio(exec, 1);
		return (exec->exit);
	}
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