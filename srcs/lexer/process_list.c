/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:04:54 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/05 14:50:11 by julolle-         ###   ########.fr       */
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

void	create_fd(t_proc *lst_proc, char *name_file, int type)
{
	lst_proc->outfile = name_file;
	if (type == 4)
		lst_proc->fd[1] = open(name_file, O_CREAT | O_RDWR | O_TRUNC, 0666);
	else
		lst_proc->fd[1] = open(name_file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (lst_proc->fd[1] < 0)
	{
		lst_proc->fd[1] = -1;
		ft_printf("Error open outfile\n"); //manage error chao program????
	}
}

void	find_outfile(t_proc *lst_proc, t_tok **lst_tok, int *err)
{
	int		type;
	char	*name_file;

	if (lst_proc->outfile)
		free(lst_proc->outfile);
	type = (*lst_tok)->type;
	if ((*lst_tok)->next && ((*lst_tok)->next->type <= 2 || \
		((*lst_tok)->next->type == 3 && (*lst_tok)->next->next && \
		(*lst_tok)->next->next->type <= 2)))
	{
		*lst_tok = (*lst_tok)->next;
		if ((*lst_tok)->type == 3 && (*lst_tok)->next)
			(*lst_tok) = (*lst_tok)->next;
		name_file = join_str_toks(lst_tok);
		if (!name_file)
		{
			msg_error_parsing(12, err);
			return ;
		}
		create_fd(lst_proc, name_file, type);
	}
	else
	{
		lst_proc->fd[1] = -1;
		ft_printf("No outfile\n"); //manage error chao program*/
	}
}

void	find_infile(t_proc *lst_proc, t_tok **lst_tok, int *err)
{
	char	*name_file;

	if (lst_proc->infile)
		free(lst_proc->infile);
	if ((*lst_tok)->next && ((*lst_tok)->next->type <= 2 || \
		((*lst_tok)->next->type == 3 && (*lst_tok)->next->next && \
		(*lst_tok)->next->next->type <= 2)))
	{
		*lst_tok = (*lst_tok)->next;
		if ((*lst_tok)->type == 3 && (*lst_tok)->next)
			(*lst_tok) = (*lst_tok)->next;
		name_file = join_str_toks(lst_tok);
		if (!name_file)
		{
			msg_error_parsing(12, err);
			return ;
		}
		lst_proc->infile = name_file;
		lst_proc->fd[0] = open(name_file, O_RDONLY);
		if (lst_proc->fd[0] < 0)
		{
			lst_proc->fd[0] = -1;
			ft_printf("Error open infile\n"); //manage error chao program????
		}
	}
	else
	{
		ft_printf("No infile\n"); //manage error chao program
		lst_proc->fd[0] = -1;
	}
}

void	find_heredoc(t_proc *lst_proc, t_tok **lst_tok)
{
	char	*str_lim;

	if (lst_proc->hd_lim)
		free(lst_proc->hd_lim);
	if ((*lst_tok)->next && ((*lst_tok)->next->type <= 2 || \
		((*lst_tok)->next->type == 3 && (*lst_tok)->next->next && \
		(*lst_tok)->next->next->type <= 2)))
	{
		*lst_tok = (*lst_tok)->next;
		if ((*lst_tok)->type == 3 && (*lst_tok)->next)
			(*lst_tok) = (*lst_tok)->next;
		str_lim = join_str_toks(lst_tok);
		lst_proc->hd_lim = ft_strdup(str_lim);
		free(str_lim);
	}
	else
	{
		ft_printf("No heredoc str limit\n"); //manage error chao program
		lst_proc->hd_lim = NULL;
	}
}

void	create_array(t_proc *lst_proc, t_tok **lst_tok, int *i)
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
		*lst_tok = (*lst_tok)->next;
	}
	if (str_join)
	{
		lst_proc->arg[*i] = ft_strdup(str_join);
		free(str_join);
	}
	else
		lst_proc->arg[*i] = ft_strdup((*lst_tok)->str);
	*i = *i + 1;
}

t_proc	*create_node_process(t_proc **lst_proc, t_tok **lst_tok, int pos, int *err)
{
	int		n_arg;
	t_tok	*tmp;
	t_proc	*proc;

	tmp = *lst_tok;
	n_arg = 0;
	while (*lst_tok && (*lst_tok)->type != 8)
	{
		if (((*lst_tok)->type <= 2) && ((*lst_tok)->prev == NULL || (*lst_tok)->prev->type == 8))
			n_arg++;
		else if (((*lst_tok)->type <= 2) && ((*lst_tok)->prev->prev && (*lst_tok)->prev->type == 3 && \
			((*lst_tok)->prev->prev->type < 4 || (*lst_tok)->prev->prev->type == 8)))
			n_arg++;
		*lst_tok = (*lst_tok)->next;
	}
	*lst_tok = tmp;
	ft_lstadd_back_proc(lst_proc, ft_lstnew_proc(err), err);
	proc = ft_lstlast_proc(*lst_proc);
	proc->pos = pos;
	proc->arg = malloc(sizeof(char *) * (n_arg + 1));
	if (!proc->arg)
	{
		msg_error_parsing(12, err);
		return (NULL);
	}
	proc->arg[n_arg] = NULL;
	return (proc);
}

void	new_process(t_proc **lst_proc, t_tok *lst_tok, int pos, int *err)
{
	t_proc	*proc;
	int		pos_str;

	proc = NULL;
	pos_str = 0;
	proc = create_node_process(lst_proc, &lst_tok, pos, err);
	if (!proc)
		return ;
	while (lst_tok && lst_tok->type != 8)
	{
		if (lst_tok->type == 4 || lst_tok->type == 5)
			find_outfile(proc, &lst_tok, err);
		else if (lst_tok->type == 6)
			find_infile(proc, &lst_tok, err);
		else if (lst_tok->type == 7)
			find_heredoc(proc, &lst_tok);
		else if (lst_tok->type <= 2)
			create_array(proc, &lst_tok, &pos_str);
		lst_tok = lst_tok->next;
	}
}

int	create_process(t_proc **lst_proc, t_tok **lst_tok, int *err)
{
	int		pos_proc;
	t_tok	*tmp;

	tmp = *lst_tok;
	pos_proc = 0;
	(void)lst_proc;
	
	while (*lst_tok)
	{
		new_process(lst_proc, *lst_tok, pos_proc++, err);
		if (*err)
			break ;
		while (*lst_tok && (*lst_tok)->type != 8)
			*lst_tok = (*lst_tok)->next;
		if ((*lst_tok))
			*lst_tok = (*lst_tok)->next;
	}
	*lst_tok = tmp;
	//ft_print_process(lst_proc);
	return (*err);
}
