/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:54:07 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/26 20:09:02 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str(t_proc *lst_proc)
{
	int	i;

	i = 0;
	if (lst_proc->arg)
	{
		while (lst_proc->arg[i])
		{
			free(lst_proc->arg[i]);
			i++;
		}
		free(lst_proc->arg);
		lst_proc->arg = NULL;
	}
	i = 0;
	if (lst_proc->hd_lim)
	{
		while (lst_proc->hd_lim[i])
		{
			free(lst_proc->hd_lim[i]);
			i++;
		}
		free(lst_proc->hd_lim);
		lst_proc->hd_lim = NULL;
	}
}

void	free_lst_proc(t_proc **lst_proc)
{
	t_proc	*tmp;

	if (!lst_proc || !(*lst_proc))
		return ;
	while (*lst_proc)
	{
		tmp = (*lst_proc)->next;
		free_str(*lst_proc);
		if ((*lst_proc)->infile)
			free((*lst_proc)->infile);
		if ((*lst_proc)->outfile)
			free((*lst_proc)->outfile);
		if ((*lst_proc)->fd[0] > 0)
			close((*lst_proc)->fd[0]);
		if ((*lst_proc)->fd[1] > 0)
			close((*lst_proc)->fd[1]);
		free(*lst_proc);
		(*lst_proc) = NULL;
		*lst_proc = tmp;
	}
	lst_proc = NULL;
}

void	free_lst_tok(t_tok **lst_tok)
{
	t_tok	*tmp;

	while (*lst_tok)
	{
		tmp = (*lst_tok)->next;
		if ((*lst_tok)->str)
			free((*lst_tok)->str);
		free(*lst_tok);
		*lst_tok = tmp;
	}
}
