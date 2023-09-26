/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_free_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:54:07 by julolle-          #+#    #+#             */
/*   Updated: 2023/09/26 15:32:07 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_lst_proc(t_proc **lst_proc)
{
	t_proc	*tmp;

	while (*lst_proc)
	{
		tmp = (*lst_proc)->next;
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
		while ((*lst_proc)->arg[i])
		{
			printf("arg[%i]-> '%s'\n", i, (*lst_proc)->arg[i]);
			i++;
		}
		printf("arg[%i]-> '%s'\n", i, (*lst_proc)->arg[i]);
		printf("outfile-> '%s'	fd:%i\n", (*lst_proc)->outfile, (*lst_proc)->fd[1]);
		printf("infile->0 '%s'	fd:%i\n", (*lst_proc)->infile, (*lst_proc)->fd[0]);
		(*lst_proc) = (*lst_proc)->next;
	}
	*lst_proc = tmp;
	free_lst_proc(lst_proc);
}

void	free_lst(t_tok **lst_tok)
{
	t_tok	*tmp;

	while (*lst_tok)
	{
		tmp = (*lst_tok)->next;
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
	free_lst(lst_tok);
}
