/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:19:21 by julolle-          #+#    #+#             */
/*   Updated: 2023/09/21 19:05:09 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char    *line;
	t_tok	*lst_tok;
	t_proc	*lst_proc;
	
	lst_tok = NULL;
	while(1)
	{
		line = readline("minishell$");
		if (line)
		   add_history(line);
		if (!ft_strncmp(line, "exit", 5))
			break;
		create_tokens(&lst_tok, line);
		//ft_print_list(lst_tok);
		sep_process(&lst_proc, &lst_tok);
		ft_print_process(lst_proc);
	}
  return (0);
}
