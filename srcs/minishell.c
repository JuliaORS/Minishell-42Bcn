/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:19:21 by julolle-          #+#    #+#             */
/*   Updated: 2023/09/27 16:12:36 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	int		exit_status;
	t_tok	*lst_tok;
	t_proc	*lst_proc;

	(void)argc;
	(void)argv;
	(void)env;
	exit_status = 0;
	lst_tok = NULL;
	while (1)
	{
		line = readline("minishell$");
		if (line)
			add_history(line);
		if (!ft_strncmp(line, "exit", 5))
			break ;
		if (!parsing_input(line, &exit_status))
		{	
			create_tokens(&lst_tok, line, &exit_status);
			//ft_print_list_tok(&lst_tok);
			create_process(&lst_proc, &lst_tok);
			//ft_print_process(&lst_proc);
		}
	}
	return (0);
}
