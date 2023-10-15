/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:04:54 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/15 12:30:24 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_array_hdoc(t_proc *proc, t_tok **lst_tok)
{
	int		n_hdoc;
	t_tok	*tmp;

	tmp = *lst_tok;
	n_hdoc = 0;
	while (*lst_tok && (*lst_tok)->type != 8)
	{
		if ((*lst_tok)->type == 7)
			n_hdoc++;
		*lst_tok = (*lst_tok)->next;
	}
	proc->hd_lim = (char **)malloc(sizeof(char *) * (n_hdoc + 1));
	if (!proc->hd_lim)
		return (1);
	proc->hd_lim[n_hdoc] = NULL;
	*lst_tok = tmp;
	return (0);
}

int	create_array_arg(t_proc *proc, t_tok **lst_tok)
{
	int		n_arg;
	t_tok	*tmp;

	tmp = *lst_tok;
	n_arg = 0;
	while (*lst_tok && (*lst_tok)->type != 8)
	{
		if (((*lst_tok)->type <= 2) && ((*lst_tok)->prev == NULL || \
			(*lst_tok)->prev->type == 8))
			n_arg++;
		else if (((*lst_tok)->type <= 2) && ((*lst_tok)->prev->prev && \
			(*lst_tok)->prev->type == 3 && ((*lst_tok)->prev->prev->type < 4 || \
			(*lst_tok)->prev->prev->type == 8)))
			n_arg++;
		*lst_tok = (*lst_tok)->next;
	}
	proc->arg = (char **)malloc(sizeof(char *) * (n_arg + 1));
	if (!proc->arg)
		return (1);
	proc->arg[n_arg] = NULL;
	*lst_tok = tmp;
	return (0);
}

t_proc	*create_node_proc(t_proc **lst_proc, t_tok **lst_tok, int pos)
{
	t_proc	*proc;

	proc = ft_lstnew_proc();
	if (!proc)
		return (NULL);
	ft_lstadd_back_proc(lst_proc, proc);
	proc->pos = pos;
	create_array_arg(proc, lst_tok);
	if (create_array_arg(proc, lst_tok))
		return (NULL);
	if (create_array_hdoc(proc, lst_tok))
		return (NULL);
	return (proc);
}

int	new_process(t_proc **lst_proc, t_tok **lst_tok, int pos, int *exit)
{
	t_proc	*proc;
	int		n_str;
	int		n_hd;

	n_str = 0;
	n_hd = 0;
	proc = create_node_proc(lst_proc, lst_tok, pos);
	if (!proc)
		return (msg_error_parsing(12, 0, exit));
	while (*lst_tok && (*lst_tok)->type != 8 && !*exit)
	{
		if ((*lst_tok)->type == 4 || (*lst_tok)->type == 5)
			find_outfile(proc, lst_tok, exit);
		else if ((*lst_tok)->type == 6)
			find_infile(proc, lst_tok, exit);
		else if ((*lst_tok)->type == 7)
			find_heredoc(proc, lst_tok, n_hd++, exit);
		else if ((*lst_tok)->type <= 2)
			create_str(proc, lst_tok, n_str++, exit);
		if (*lst_tok)
			*lst_tok = (*lst_tok)->next;
	}
	return (*exit);
}

int	create_process(t_proc **lst_proc, t_tok **lst_tok, int *exit)
{
	int		pos_proc;
	t_tok	*tmp;

	*lst_proc = NULL;
	tmp = *lst_tok;
	pos_proc = 0;
	while (*lst_tok && !*exit)
	{
		if (new_process(lst_proc, lst_tok, pos_proc, exit))
			break ;
		if ((*lst_tok))
			*lst_tok = (*lst_tok)->next;
		pos_proc++;
	}
	*lst_tok = tmp;
	return (*exit);
}
