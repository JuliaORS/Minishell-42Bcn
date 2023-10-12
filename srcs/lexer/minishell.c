/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:19:21 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/12 17:58:45 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_loop(t_exec *exec, t_proc **lst_proc, char **env)
{
	char	*input;

	while (1)
	{
		init_signals(READ, &exec.exit[0]);
		input = readline("minishell$🦄");
		if (input)
			add_history(input);
		if (!input || !ft_strncmp(input, "exit", 5))
		{
			ft_printf("exit\n");
			break ;
		}
		init_error(exec);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		exec.exit[0] = manage_input(input, &lst_proc, &exec.exit[0]);
		if(!exec.exit[0])
		{
			exec.total_cmd = measure_list(&lst_proc);
			if(!manage_heredoc(&lst_proc, &exec.exit[0]))
				exec.exit[0] = exec_machine(lst_proc, &exec);
		}
		free (input);
		free_lst_proc(lst_proc);
	}
	free (input);
	free_lst_proc(lst_proc);
}

int	main(int argc, char **argv, char **env)
{
	t_exec	exec;
	t_proc	*lst_proc;

	lst_proc = NULL;
	(void)argc;
	(void)argv;

	init_exec(&exec, env);
	main_loop(&exec, &lst_proc, env);
	rl_clear_history();
	return (0);
}
