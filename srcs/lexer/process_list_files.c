/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_list_files.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:03:53 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/25 13:43:26 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_str_toks(t_tok **lst_tok)
{
	char	*str_join;	
	char	*str_tmp;

	str_join = NULL;
	while ((*lst_tok)->next && (*lst_tok)->next->type <= 2)
	{
		if (!str_join)
			str_join = ft_strjoin((*lst_tok)->str, (*lst_tok)->next->str);
		else
		{
			str_tmp = str_join;
			str_join = ft_strjoin(str_join, (*lst_tok)->next->str);
			free(str_tmp);
		}
		if (!str_join)
			return (NULL);
		*lst_tok = (*lst_tok)->next;
	}
	if (!str_join)
		str_join = ft_strdup((*lst_tok)->str);
	return (str_join);
}

int	find_outfile(t_proc *lst_proc, t_tok **lst_tok, int *exit)
{
	int		type;
	
	if (lst_proc->outfile)
	{
		close (lst_proc->fd[1]);
		free(lst_proc->outfile);
	}
	type = (*lst_tok)->type;
	*lst_tok = (*lst_tok)->next;
	if ((*lst_tok)->type == 3)
		(*lst_tok) = (*lst_tok)->next;
	lst_proc->outfile = join_str_toks(lst_tok);
	if (!lst_proc->outfile)
		return (err_msg_parser(MALLOC_MESS, 12, 0, exit));
	if (type == 4)
		lst_proc->fd[1] = open(lst_proc->outfile, O_CREAT | O_RDWR | \
		O_TRUNC, 0666);
	else
		lst_proc->fd[1] = open(lst_proc->outfile, O_WRONLY | O_CREAT | \
		O_APPEND, 0666);
	return (0);
}

int	find_infile(t_proc *lst_proc, t_tok **lst_tok, int *exit)
{
	lst_proc->intype = 0;
	if (lst_proc->infile)
	{
		close (lst_proc->fd[0]);
		free(lst_proc->infile);
	}
	*lst_tok = (*lst_tok)->next;
	if ((*lst_tok)->type == 3 && (*lst_tok)->next)
		(*lst_tok) = (*lst_tok)->next;
	lst_proc->infile = join_str_toks(lst_tok);
	if (!lst_proc->infile)
		return (err_msg_parser(MALLOC_MESS, 12, 0, exit));
	lst_proc->fd[0] = open(lst_proc->infile, O_RDONLY);
	return (0);
}

int	find_heredoc(t_proc *lst_proc, t_tok **lst_tok, int n_hd, int *exit)
{
	lst_proc->intype = 1;
	*lst_tok = (*lst_tok)->next;
	if ((*lst_tok)->type == 3 && (*lst_tok)->next)
		(*lst_tok) = (*lst_tok)->next;
	lst_proc->hd_lim[n_hd] = join_str_toks(lst_tok);
	if (!lst_proc->hd_lim)
		return (err_msg_parser(MALLOC_MESS, 12, 0, exit));
	return (0);
}

int	create_str(t_proc *lst_proc, t_tok **lst_tok, int n_str, int *exit)
{
	lst_proc->arg[n_str] = join_str_toks(lst_tok);
	if (!lst_proc->arg[n_str])
		return (err_msg_parser(MALLOC_MESS, 12, 0, exit));
	return (0);
}
