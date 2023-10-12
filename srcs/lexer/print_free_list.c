/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_free_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:54:07 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/12 15:32:58 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lst_proc(t_proc **lst_proc)
{
	t_proc	*tmp;
	int		i;

	if (!lst_proc)
		return  ;
	while (*lst_proc)
	{
		i = 0;
		tmp = (*lst_proc)->next;
		if ((*lst_proc)->arg)
		{
			while ((*lst_proc)->arg[i])
			{
				free((*lst_proc)->arg[i]);
				i++;
			}
			free((*lst_proc)->arg);
		}
		if ((*lst_proc)->infile)
			free((*lst_proc)->infile);
		if ((*lst_proc)->outfile)
			free((*lst_proc)->outfile);
		i = 0;
		if ((*lst_proc)->hd_lim)
		{
			while ((*lst_proc)->hd_lim[i])
			{
				free((*lst_proc)->hd_lim[i]);
				i++;
			}
			free((*lst_proc)->hd_lim);
		}
		if ((*lst_proc)->fd[0] > 0)
			close((*lst_proc)->fd[0]);
		if ((*lst_proc)->fd[1] > 0)
			close((*lst_proc)->fd[1]);
		free(*lst_proc);
		*lst_proc = tmp;
	}
	lst_proc = NULL;
}

void	ft_print_process(t_proc **lst_proc)
{
	int		i;
	t_proc	*tmp;

	tmp = *lst_proc;
	i = 0;
	while (*lst_proc)
	{
		i = 0;
		printf ("\nNUM PROCESS: %i\n", (*lst_proc)->pos);
		if((*lst_proc)->arg)
		{
			while ((*lst_proc)->arg[i])
			{
				printf("arg[%i]-> '%s'\n", i, (*lst_proc)->arg[i]);
				i++;
			}
		}
		printf("arg[%i]-> '%s'\n", i, (*lst_proc)->arg[i]);
		i = 0;
		printf("outfile-> '%s'	fd:%i\n", (*lst_proc)->outfile, (*lst_proc)->fd[1]);
		printf("infile-> '%s'	fd:%i\n", (*lst_proc)->infile, (*lst_proc)->fd[0]);
		if((*lst_proc)->hd_lim)
		{
			while ((*lst_proc)->hd_lim[i])
			{
				printf("heredoc[%i]-> '%s'\n", i, (*lst_proc)->hd_lim[i]);
				i++;
			}
		}
		(*lst_proc) = (*lst_proc)->next;
	}
	*lst_proc = tmp;
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

void	ft_print_list_tok(t_tok **lst_tok)
{
	t_tok	*tmp;

	tmp = *lst_tok;
	while (*lst_tok)
	{
		printf("string: %s // type: %i\n", (*lst_tok)->str, (*lst_tok)->type);
		*lst_tok = (*lst_tok)->next;
	}
	*lst_tok = tmp;
}
