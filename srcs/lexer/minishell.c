/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:19:21 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/09 15:17:39 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_exec	exec;
	t_proc	*lst_proc;

	(void)argc;
	(void)argv;
	(void)env;
	while (1)
	{
		init_signals(READ, &exec.exit);
		input = readline("minishell$🦄");
		if (input)
			add_history(input);
		if (!ft_strncmp(input, "exit", 5))
			break ;
		exec.exit = manage_input(input, &lst_proc, &exec.exit);
		if(!exec.exit)
		{
			init_exec(&exec, lst_proc, env);
			if(!manage_heredoc(&lst_proc, &exec.exit))
				exec.exit = exec_machine(lst_proc, &exec);
			//printf("go execution\n");
		}
		free (input);
		free_lst_proc(&lst_proc);
	}
	free(input);
	free_lst_proc(&lst_proc);
	rl_clear_history();
	return (0);
}
