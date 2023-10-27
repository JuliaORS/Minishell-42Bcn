/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:02:59 by rjobert           #+#    #+#             */
/*   Updated: 2023/10/27 13:03:01 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_fd_msg(char *msg, t_exec *exec, t_proc *pcs, char *fname)
{
	ft_printf(STDERR_FILENO, "minishell: %s: %s\n", fname, msg);
	if (exec)
		free_exec(&exec);
	if (exec->in_parent && is_builtin(pcs))
		return (EXIT_FAILURE);
	else
		exit(EXIT_FAILURE);
}

/*
check that any infile or outfile used in prompt exist or are ok permission-wise
*/
int	check_io_fd(t_proc *pcs, t_exec *exec)
{
	struct stat	st;

	if (pcs->fd[0] == -1)
	{
		if (!stat(pcs->infile, &st) && S_ISDIR(st.st_mode))
			return (error_fd_msg("Is a directory", exec, pcs, pcs->infile));
		if (!access(pcs->infile, F_OK) && access(pcs->infile, R_OK))
			return (error_fd_msg("Permission denied", exec, pcs, pcs->infile));
		if (access(pcs->infile, F_OK))
			return (error_fd_msg("No such file or directory", exec, pcs, \
			pcs->infile));
		return (EXIT_FAILURE);
	}
	if (pcs->fd[1] == -1)
	{
		if (!stat(pcs->outfile, &st) && S_ISDIR(st.st_mode))
			return (error_fd_msg("Is a directory", exec, pcs, pcs->outfile));
		if (!access(pcs->outfile, F_OK) && access(pcs->outfile, W_OK))
			return (error_fd_msg("Permission denied", exec, pcs, pcs->outfile));
		if (access(pcs->outfile, F_OK))
			return (error_fd_msg("No such file or directory", exec, pcs, \
			pcs->outfile));
		return (EXIT_FAILURE);
	}
	return (0);
}

/*
avoid dangling poitner and double free
*/
void	free_pntr(void *pntr)
{
	if (pntr != NULL)
	{
		free(pntr);
		pntr = NULL;
	}
}
