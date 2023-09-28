/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:04:54 by julolle-          #+#    #+#             */
/*   Updated: 2023/09/28 14:53:25 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_outfile(t_proc *lst_proc, t_tok **lst_tok)
{
	int	type;

	type = (*lst_tok)->type;
	if ((*lst_tok)->next)
	{
		*lst_tok = (*lst_tok)->next;
		if ((*lst_tok)->type == 3 && (*lst_tok)->next)
			(*lst_tok) = (*lst_tok)->next;
		if ((*lst_tok)->type <= 2)
		{
			if (type == 4)
			{
				lst_proc->outfile = ft_strdup((*lst_tok)->str);
				lst_proc->fd[1] = open((*lst_tok)->str, O_CREAT | O_RDWR | O_TRUNC, 0666);
			}
			else
			{
				lst_proc->outfile = ft_strdup((*lst_tok)->str);
				lst_proc->fd[1] = open((*lst_tok)->str, O_WRONLY | O_CREAT | O_APPEND, 0666);
			}
			if (lst_proc->fd[1] < 0)
			{
				lst_proc->fd[1] = -1;
				printf("Error open outfile\n"); //manage error chao program????
			}
		}
	}
	else
	{
		lst_proc->fd[1] = -1;
		printf("No outfile\n"); //manage error chao program*/
	}
}

void	create_infile(t_proc *lst_proc, t_tok **lst_tok)
{
	if ((*lst_tok)->next)
	{
		*lst_tok = (*lst_tok)->next;
		if ((*lst_tok)->type == 3 && (*lst_tok)->next)
			(*lst_tok) = (*lst_tok)->next;
		if ((*lst_tok)->type <= 2)
		{
			lst_proc->infile = ft_strdup((*lst_tok)->str);
			lst_proc->fd[0] = open((*lst_tok)->str, O_RDONLY);
			if (lst_proc->fd[0] < 0)
			{
				lst_proc->fd[0] = -1;
				printf("Error open infile\n"); //manage error chao program????
			}
		}
	}
	else
	{
		printf("No infile\n"); //manage error chao program
		lst_proc->fd[0] = -1;
	}
}

void	create_array(t_proc *lst_proc, t_tok **lst_tok, int *i)
{
	char	*str_join;	

	str_join = NULL;
	while ((*lst_tok)->next && (*lst_tok)->next->type <= 2)
	{
		if (!str_join)
			str_join = ft_strjoin((*lst_tok)->str, (*lst_tok)->next->str);
		else
			str_join = ft_strjoin(str_join, (*lst_tok)->next->str);
		*lst_tok = (*lst_tok)->next;
	}
	if (str_join)
		lst_proc->arg[*i] = str_join;
	else
		lst_proc->arg[*i] = (*lst_tok)->str;
	*i = *i + 1;
}

void	create_node_process(t_proc **lst_proc, t_tok **lst_tok, int pos, t_proc **proc, int *err)
{
	int		n_arg;
	t_tok	*tmp;

	tmp = *lst_tok;
	n_arg = 0;
	while (*lst_tok && (*lst_tok)->type != 8)
	{
		if (((*lst_tok)->type <= 2) && ((*lst_tok)->prev == NULL || (*lst_tok)->prev->type == 8))
			n_arg++;
		else if (((*lst_tok)->type <= 2) && ((*lst_tok)->prev->type == 3 && \
			((*lst_tok)->prev->prev->type < 4 || (*lst_tok)->prev->prev->type > 7)))
			n_arg++;
		*lst_tok = (*lst_tok)->next;
	}
	*lst_tok = tmp;
	ft_lstadd_back_proc(lst_proc, ft_lstnew_proc(err), err);
	*proc = ft_lstlast_proc(*lst_proc);
	(*proc)->pos = pos;
	(*proc)->arg = malloc(sizeof(char *) * (n_arg + 1));
	if (!(*proc)->arg)
		msg_error_parsing(12, err);
	(*proc)->arg[n_arg] = NULL;
}

void	new_process(t_proc **lst_proc, t_tok *lst_tok, int pos, int *err)
{
	t_proc	*proc;
	int		pos_str;

	proc = NULL;
	pos_str = 0;
	create_node_process(lst_proc, &lst_tok, pos, &proc, err);
	while (lst_tok && lst_tok->type != 8)
	{
		if (lst_tok->type == 4 || lst_tok->type == 5)
			create_outfile(proc, &lst_tok);
		else if (lst_tok->type == 6)
			create_infile(proc, &lst_tok);
		else if (lst_tok->type == 7)
			printf("heredoc\n");
		else if (lst_tok->type <= 2)
			create_array(proc, &lst_tok, &pos_str);
		lst_tok = lst_tok->next;
	}
}

int	create_process(t_proc **lst_proc, t_tok **lst_tok, int *err)
{
	int		pos_proc;
	t_proc	**tmp;
	
	tmp = lst_proc;
	pos_proc = 0;
	printf("hola\n");
	while (*lst_tok)
	{
		new_process(lst_proc, *lst_tok, pos_proc++, err);
		ft_print_process(lst_proc);
		if (*err)
			break ;
		while (*lst_tok && (*lst_tok)->type != 8)
			*lst_tok = (*lst_tok)->next;
		if ((*lst_tok))
			*lst_tok = (*lst_tok)->next;
	}
	lst_proc = tmp;
	//ft_print_process(lst_proc);
	return (*err);
}
