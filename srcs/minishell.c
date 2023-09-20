/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:19:21 by julolle-          #+#    #+#             */
/*   Updated: 2023/09/20 15:29:11 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*void	create_outfile(t_proc **lst_proc, t_tok *lst_tok)
{
	t_tok	*tmp;
	
	tmp = lst_tok;
	if (lst_tok->next->type != 0 && lst_tok->next->type != 1 && lst_tok->next->type != 2)
		printf("Error\n"); //manage error
	else
	{
		*lst_proc
	}
}

void create_process(t_proc **lst_proc, t_tok *lst_tok)
{
	t_tok	*tmp;

	tmp = lst_tok;
	(void)lst_proc;
	while (lst_tok)
	{
		
		while(lst_tok && lst_tok->type != 8)
		{
			if (lst_tok->type == 4 || lst_tok->type == 5)
				create_outfile(lst_proc, lst_tok);
			else if (lst_tok->type == 6)
				printf("infile\n");
			else if (lst_tok->type == 7) 
				printf("heredoc\n");
			else if (lst_tok->type == 0 || lst_tok->type == 1 || lst_tok->type == 2)
				printf("str\n");
			lst_tok = lst_tok->next;
		}
		if (lst_tok)
			lst_tok = lst_tok->next;
		printf("un pipe\n");
	}
}*/

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char    *line;
	t_tok	*lst_tok;
	//t_proc	*lst_proc;
	
	lst_tok = NULL;
	while(1)
	{
		line = readline("minishell$");
		if (line)
		   add_history(line);
		if (!ft_strncmp(line, "exit", 4))
			break;
		create_tokens(&lst_tok, line);
		ft_print_list(lst_tok);
		//create_process(&lst_proc, lst_tok);
	}
  return (0);
}
