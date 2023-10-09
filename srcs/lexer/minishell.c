/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:19:21 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/05 14:50:27 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;
	int		err;
	t_proc	*lst_proc;

	(void)argc;
	(void)argv;
	while (1)
	{
		init_signals(READ, &err);
		input = readline("minishell$🦄");
		if (input)
			add_history(input);
		if (!ft_strncmp(input, "exit", 5))
			break ;
		if (!manage_input(input, &lst_proc, &err))
		{
			//if(!manage_heredoc(&lst_proc, &err))
			err = exec_machine(lst_proc, env);
		}
		free (input);
		free_lst_proc(&lst_proc);
	}
	free(input);
	free_lst_proc(&lst_proc);
	rl_clear_history();
	return (0);
}
