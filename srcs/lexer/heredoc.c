/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:08:01 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/09 15:11:28 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_hd(char *str, int *err)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			str = check_expand(str, &i, err);
			if (!str)
				return (NULL);
		}
		i++;
	}
	return (str);
}

void	save_hd(t_proc *lst_proc, char *str, int *fds)
{
	write(fds[1], str, ft_strlen(str));
	close(fds[1]);
	close(fds[0]);
	if (lst_proc->intype == 1)
		lst_proc->fd[0] = fds[0];
}

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
	if (!str_join)
		return (NULL);
	str_final = ft_strjoin(str_join, "\n");
	free(str_join);
	if (!str_final)
		return (NULL);
	return (str_final);
}

int	create_input_hd(t_proc *lst_proc, int *fds, int n_hd, int *err)
{
	char	*input_hd;
	char	*hd_text;
	char	*str_exp;

	hd_text = NULL;
	while (1)
	{
		input_hd = readline("> ");
		if (input_hd)
			add_history(input_hd);
		if (!ft_strncmp(input_hd, lst_proc->hd_lim[n_hd], ft_strlen(lst_proc->hd_lim[n_hd]) + 1))
			break ;
		hd_text = join_input(input_hd, hd_text);
		if (!hd_text)
			return (12);
		free (input_hd);
	}
	free (input_hd);
	str_exp = expand_hd(hd_text, err);
	save_hd(lst_proc, str_exp, fds);
	return (0);
}

int	check_hd_exit(void)
{
	int		exit_process;

	waitpid (-1, &exit_process, 0);
	if (WEXITSTATUS(exit_process) == 12)
	{
		ft_printf("error in save heredoc\n"); //manage error
		return (12);
	}
	else if (WEXITSTATUS(exit_process) == 1)
	{
		ft_printf("receive signal ctrl+c\n"); //manage error
		return (1);
	}
	return (0);
}

void	exec_hd(t_proc *proc, int n_hd, int *err)
{
	int		fds[2];
	int		pid;
	int		exit_hd;

	pipe(fds);
	pid = fork ();
	if (pid == 0)
	{
		init_signals(HEREDOC, err);
		exit_hd = create_input_hd(proc, fds, n_hd, err);
		exit (exit_hd);
	}
	close(fds[1]);
	*err = check_hd_exit();
}

int	manage_heredoc(t_proc **lst_proc, int *err)
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
				exec_hd(*lst_proc, n_hd, err);
				if (*err)
				{
					msg_error_parsing(*err, err);
					break ;
				}
				n_hd++;
			}
		}
		(*lst_proc) = (*lst_proc)->next;
	}
	*lst_proc = tmp;
	return (*err);
}
