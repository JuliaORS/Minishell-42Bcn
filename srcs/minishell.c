/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:19:21 by julolle-          #+#    #+#             */
/*   Updated: 2023/09/28 14:36:21 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	int		err;
	t_proc	*lst_proc;

	(void)argc;
	(void)argv;
	(void)env;
	while (1)
	{
		line = readline("minishell$");
		if (line)
			add_history(line);
		if (!ft_strncmp(line, "exit", 5))
			break ;
		if (!manage_input(line, &lst_proc, &err))
		{	
			printf("go ahead with execution!\n");
			///EXECUTION
		}
	}
	return (0);
}
