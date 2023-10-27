/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:08:01 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/26 19:23:27 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_input(char *input_hd, char *hd_text)
{
	char	*str_join;
	char	*str_final;

	if (!hd_text)
		str_join = ft_strdup(input_hd);
	else
	{
		str_join = ft_strjoin(hd_text, input_hd);
		free(hd_text);
	}
	free (input_hd);
	if (!str_join)
		return (NULL);
	str_final = ft_strjoin(str_join, "\n");
	free(str_join);
	return (str_final);
}

int	create_input_hd(t_proc *lst_proc, int *fds, int n_hd, t_exec *exec)
{
	char	*input_hd;
	char	*hd_text;
	char	*str_exp;
	int		flag_exp;

	flag_exp = 0;
	init_signals(HEREDOC);
	hd_text = NULL;
	while (1)
	{
		input_hd = readline("> ");
		if (!input_hd || !ft_strncmp(input_hd, lst_proc->hd_lim[n_hd], \
			ft_strlen(lst_proc->hd_lim[n_hd]) + 1))
			break ;
		hd_text = join_input(input_hd, hd_text);
		if (!hd_text)
			return (12);
	}
	free (input_hd);
	str_exp = find_dollar_sign(hd_text, exec, &flag_exp);
	if (!str_exp)
		return (12);
	write(fds[1], str_exp, ft_strlen(str_exp));
	free(str_exp);
	return (0);
}

int	check_hd_exit(int pid, t_exec *exec, int fd0, int fd1)
{
	int		exit_process;

	waitpid (pid, &exit_process, 0);
	if (WEXITSTATUS(exit_process) == 12)
	{
		exec->exit[0] = 12;
		return (12);
	}
	else if (WEXITSTATUS(exit_process) == 1)
	{
		exec->exit[0] = 1;
		return (1);
	}
	close(fd1);
	if (exec->exit[0])
		close(fd0);
	if (exec->exit[0] == 12)
		err_msg_parser(MALLOC_MESS, 12, 0, &exec->exit[0]);
	return (exec->exit[0]);
}

int	exec_hd(t_proc *proc, int n_hd, t_exec *exec)
{
	int		fds[2];
	int		pid;
	int		exit_hd;

	pipe(fds);
	pid = fork ();
	if (pid == -1)
		error_msg("fork failed", ENOMEM, exec, NULL);
	if (pid == 0)
	{
		exit_hd = create_input_hd(proc, fds, n_hd, exec);
		close(fds[1]);
		close(fds[0]);
		exit (exit_hd);
	}
	check_hd_exit(pid, exec, fds[0], fds[1]);
	if (proc->intype == 1)
	{
		if (proc->fd[0])
			close(proc->fd[0]);
		proc->fd[0] = fds[0];
	}
	else
		close(fds[0]);
	return (exec->exit[0]);
}

int	manage_heredoc(t_proc **lst_proc, t_exec *exec)
{
	t_proc	*tmp;
	int		n_hd;

	tmp = *lst_proc;
	while ((*lst_proc))
	{
		n_hd = 0;
		if ((*lst_proc)->hd_lim)
		{
			while ((*lst_proc)->hd_lim[n_hd])
			{
				if (exec_hd(*lst_proc, n_hd, exec))
					break ;
				n_hd++;
			}
		}
		(*lst_proc) = (*lst_proc)->next;
	}
	*lst_proc = tmp;
	return (exec->exit[0]);
}
