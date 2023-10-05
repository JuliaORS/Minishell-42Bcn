/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:08:01 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/05 14:19:53 by julolle-         ###   ########.fr       */
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
			str = check_expand(str, &i, err);
		i++;
	}
	return (str);
}

void	save_hd(t_proc *lst_proc, char *hd_text, int *fds)
{
	write(fds[1], hd_text, ft_strlen(hd_text));
	close(fds[1]);
	close(fds[0]);
	lst_proc->fd[2] = fds[0];
}

void	create_input_hd(t_proc *lst_proc, int *fds, int *err)
{
	char	*input_hd;
	char	*hd_text;
	char	*str_exp;
	char	*str_tmp;

	hd_text = NULL;
	while (1)
	{
		input_hd = readline("> ");
		if (input_hd)
			add_history(input_hd);
		if (!ft_strncmp(input_hd, lst_proc->hd_lim, \
			ft_strlen(lst_proc->hd_lim) + 1))
			break ;
		if (!hd_text)
			hd_text = ft_strdup(input_hd);
		else
		{
			str_tmp = hd_text;
			hd_text = ft_strjoin(hd_text, input_hd);
			free(str_tmp);
		}
		hd_text = ft_strjoin(hd_text, "\n");
		free (input_hd);
		if (!hd_text)
		{
			printf("error hd\n");
			*err = 12;
			return ;
		}
	}
	free (input_hd);
	str_exp = expand_hd(hd_text, err);
	save_hd(lst_proc, str_exp, fds);
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

int	manage_heredoc(t_proc **lst_proc, int *err)
{
	int		fds[2];
	int		pid;
	t_proc *tmp;

	tmp = *lst_proc;
	while ((*lst_proc))
	{
		if ((*lst_proc)->hd_lim)
		{
			pipe(fds);
			pid = fork ();
			if (pid == 0)
			{
				init_signals(HEREDOC, err);
				create_input_hd(*lst_proc, fds, err);
				if (*err == 12)
					exit (0);
				exit (0);
			}
			close(fds[1]);
			*err = check_hd_exit();
			if (*err)
				break ;
		}
		(*lst_proc) = (*lst_proc)->next;
	}
	*lst_proc = tmp;
	return (*err);
}
