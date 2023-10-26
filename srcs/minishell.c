/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:19:21 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/26 20:16:13 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_ms(char *input, t_exec *exec)
{
	t_proc	*lst_proc;

	lst_proc = NULL;
	if (ft_strlen(input) != 0)
	{
		init_error(exec);
		exec->exit[0] = manage_input(input, &lst_proc, exec);
		if (!exec->exit[0])
		{
			exec->total_cmd = measure_list(&lst_proc);
			exec->exit[0] = manage_heredoc(&lst_proc, exec);
			if (!exec->exit[0])
				exec->exit[0] = exec_machine(lst_proc, exec);
		}
		free_lst_proc(&lst_proc);
	}
}

void	main_loop(t_exec *exec)
{
	char	*input;

	while (1)
	{
		init_signals(READ);
		input = readline("minishell$🦄");
		if (input)
			add_history(input);
		if (!input)
			break ;
		signal(SIGINT, SIG_IGN);
		start_ms(input, exec);
		free (input);
	}
	free (input);
	rl_clear_history();
}

int	main(int argc, char **argv, char **env)
{
	t_exec	exec;

	(void)argv;
	if (argc != 1)
		return (1);
	init_exec(&exec, env);
	main_loop(&exec);
	return (exec.exit[0]);
}
