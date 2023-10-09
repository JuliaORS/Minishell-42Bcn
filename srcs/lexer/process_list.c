/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:04:54 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/09 15:18:16 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_array_hdoc(t_proc *proc, t_tok **lst_tok)
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
		return ;
	proc->hd_lim[n_hdoc] = NULL;
	*lst_tok = tmp;
}

void	create_array_arg(t_proc *proc, t_tok **lst_tok)
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
		return ;
	proc->arg[n_arg] = NULL;
	*lst_tok = tmp;
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
	if (!proc->arg)
		return (NULL);
	create_array_hdoc(proc, lst_tok);
	if (!proc->hd_lim)
		return (NULL);
	
	return (proc);
}

int	new_process(t_proc **lst_proc, t_tok **lst_tok, int pos, int *err)
{
	t_proc	*proc;
	int		n_str;
	int		n_hd;

	n_str = 0;
	n_hd = 0;
	proc = create_node_proc(lst_proc, lst_tok, pos);
	if (!proc)
		return(msg_error_parsing(12, err));
	while (*lst_tok && (*lst_tok)->type != 8 && !*err)
	{
		if ((*lst_tok)->type == 4 || (*lst_tok)->type == 5)
			find_outfile(proc, lst_tok, err);
		else if ((*lst_tok)->type == 6)
			find_infile(proc, lst_tok, err);
		else if ((*lst_tok)->type == 7)
			find_heredoc(proc, lst_tok, n_hd++, err);
			//printf("heredoc\n");
		else if ((*lst_tok)->type <= 2)
			create_str(proc, lst_tok, n_str++, err);
		if (*lst_tok)
			*lst_tok = (*lst_tok)->next;
	}
	return(*err);
}

int	create_process(t_proc **lst_proc, t_tok **lst_tok, int *err)
{
	int		pos_proc;
	t_tok	*tmp;

	tmp = *lst_tok;
	pos_proc = 0;
	while (*lst_tok && !*err)
	{
		if (new_process(lst_proc, lst_tok, pos_proc, err))
			break ;
		if ((*lst_tok))
			*lst_tok = (*lst_tok)->next;
			
		pos_proc++;
	}
	*lst_tok = tmp;
	//ft_print_process(lst_proc);
	return (*err);
}
