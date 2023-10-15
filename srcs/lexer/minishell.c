/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:19:21 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/15 21:08:09 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_loop(t_exec *exec)
{
	char	*input;
	t_proc	*lst_proc;

	lst_proc = NULL;
	init_error(exec);
	while (1)
	{
		init_signals(READ);
		input = readline("minishell$🦄");
		if (input)
			add_history(input);
		if (!input)
			break ;
		init_error(exec);
		signal(SIGINT, SIG_IGN);
		exec->exit[0] = manage_input(input, &lst_proc, exec);
		if (!exec->exit[0])
		{
			exec->total_cmd = measure_list(&lst_proc);
			if (!manage_heredoc(&lst_proc, exec))
				exec->exit[0] = exec_machine(lst_proc, exec);
		}
		free (input);
		free_lst_proc(&lst_proc);
	}
	free (input);
	free_lst_proc(&lst_proc);
}

int	main(int argc, char **argv, char **env)
{
	t_exec	exec;

	(void)argc;
	(void)argv;
	(void)env;
	init_exec(&exec, env);
	main_loop(&exec);
	rl_clear_history();
	return (0);
}
