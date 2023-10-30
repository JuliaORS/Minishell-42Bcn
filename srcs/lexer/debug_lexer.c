/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:56:40 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/30 15:12:30 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_process_aux(t_proc *lst_proc)
{
	int	i;

	i = 0;
	ft_printf(1, "infile-> '%s' i fd = %i\n", lst_proc->infile, \
		lst_proc->fd[0]);
	ft_printf(1, "outfile-> '%s' i fd = %i\n", lst_proc->outfile, \
		lst_proc->fd[1]);
	if (lst_proc->hd_lim)
	{
		while (lst_proc->hd_lim[i])
		{
			ft_printf(1, "heredoc[%i]-> '%s'\n", i, \
				lst_proc->hd_lim[i]);
			i++;
		}
	}
}

void	print_process_list(t_proc **lst_proc)
{
	int		i;
	t_proc	*tmp;

	tmp = *lst_proc;
	i = 0;
	while (*lst_proc)
	{
		i = 0;
		ft_printf (1, "\nNUM PROCESS: %i\n", (*lst_proc)->pos);
		if ((*lst_proc)->arg)
		{
			while ((*lst_proc)->arg[i])
			{
				ft_printf(1, "arg[%i]-> '%s'\n", i, (*lst_proc)->arg[i]);
				i++;
			}
			ft_printf(1, "arg[%i]-> '%s'\n", i, (*lst_proc)->arg[i]);
		}
		print_process_aux(*lst_proc);
		(*lst_proc) = (*lst_proc)->next;
	}
	*lst_proc = tmp;
}

void	print_tok_list(t_tok **lst_tok)
{
	t_tok	*tmp;

	tmp = *lst_tok;
	while (*lst_tok)
	{
		ft_printf(1, "string: %s	// type: %i\n", (*lst_tok)->str, \
			(*lst_tok)->type);
		*lst_tok = (*lst_tok)->next;
	}
	*lst_tok = tmp;
}
