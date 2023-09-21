/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:04:54 by julolle-          #+#    #+#             */
/*   Updated: 2023/09/21 19:32:17 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_outfile(t_proc *lst_proc, t_tok **lst_tok)
{
	int	type;
	
	type = (*lst_tok)->type;
	if ((*lst_tok)->next)
	{
		*lst_tok = (*lst_tok)->next;
		if ((*lst_tok)->type == 3 && (*lst_tok)->next)
			(*lst_tok) = (*lst_tok)->next;
		if ((*lst_tok)->type == 0 || (*lst_tok)->type == 1 || (*lst_tok)->type == 2)
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

void create_infile(t_proc *lst_proc, t_tok **lst_tok)
{
	if ((*lst_tok)->next)
	{
		*lst_tok = (*lst_tok)->next;
		if ((*lst_tok)->type == 3 && (*lst_tok)->next)
			(*lst_tok) = (*lst_tok)->next;
		if ((*lst_tok)->type == 0 || (*lst_tok)->type == 1 || (*lst_tok)->type == 2)
		{
			lst_proc->infile = ft_strdup((*lst_tok)->str);
			lst_proc->fd[0] = open((*lst_tok)->str, O_RDONLY);
			if (lst_proc->fd[0]  < 0)
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

void create_process(t_proc **lst_proc, t_tok *lst_tok, int n_arg, int pos)
{
	int	i;
	t_proc *proc;
	(void)n_arg;
	i = 0;
	ft_lstadd_back_proc(lst_proc, ft_lstnew_proc());
	proc = ft_lstlast_proc(*lst_proc);
	proc->pos = pos;
	proc->arg = malloc(sizeof(char *) * (n_arg + 1));
	proc->arg[n_arg] = NULL;
	
	while (lst_tok && lst_tok->type != 8)
	{
		if (lst_tok->type == 4 || lst_tok->type == 5)
			create_outfile(proc, &lst_tok);
		else if (lst_tok->type == 6)
			create_infile(proc, &lst_tok);
            
		else if (lst_tok->type == 7)
			printf("heredoc\n");
		else if (lst_tok->type == 0 || lst_tok->type == 1 || lst_tok->type == 2)
			proc->arg[i++] = lst_tok->str;
		lst_tok = lst_tok->next;
	}
}

void sep_process(t_proc **lst_proc, t_tok **lst_tok)
{
	int 	n_arg;
	int		pos_proc;
	t_tok	*tmp;
	
	pos_proc = 0;
	while (*lst_tok)
	{
		n_arg = 0;
		tmp = *lst_tok;
		while(*lst_tok && (*lst_tok)->type != 8)
		{
			if ((*lst_tok)->type == 0 || (*lst_tok)->type == 1 || (*lst_tok)->type == 2)
				n_arg++;
			*lst_tok = (*lst_tok)->next;
		}
		create_process(lst_proc, tmp, n_arg, pos_proc);
		pos_proc++;
		if ((*lst_tok))
			*lst_tok = (*lst_tok)->next;
	}
	
}
void	free_lst_proc(t_proc **lst_proc)
{
	t_proc	*tmp;
	
	while (*lst_proc != NULL)
	{
		tmp = (*lst_proc)->next;
		free((*lst_proc)->outfile);
		free((*lst_proc)->infile);
        *lst_proc = NULL;
		//free(*lst_proc);
		*lst_proc = tmp;
	}
    lst_proc = NULL;
    printf("hol\n");
}

void	ft_print_process(t_proc *lst_proc)
{
	int	i;
	t_proc	*tmp;
	
	tmp = lst_proc;
	i = 0;
	while (lst_proc != NULL)
	{
		i = 0;
		printf ("\nNUM PROCESS: %i\n", lst_proc->pos);
		while (lst_proc->arg[i])
		{
			printf("arg[%i]-> '%s'\n", i, lst_proc->arg[i]);
			i++;
		}	
		printf("outfile-> '%s'	fd:%i\n", lst_proc->outfile, lst_proc->fd[1]);
		printf("infile->0 '%s'	fd:%i\n", lst_proc->infile, lst_proc->fd[0]);
		lst_proc = lst_proc->next;
	}
	lst_proc = tmp;
	//printf("final out %s\n", lst_proc->outfile);
	//free_lst_proc(&lst_proc);
}
