/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:06:32 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/30 17:13:28 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	void_input(char *input)
{
	int	i;

	i = 0;
	if (!ft_strlen(input))
		return (0);
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

int	manage_input(char *line, t_proc **lst_proc, t_exec *exec)
{
	t_tok	*lst_tok;

	lst_tok = NULL;
	if (parsing_input(line, &exec->exit[0]))
		return (exec->exit[0]);
	if (create_tokens(&lst_tok, line, exec))
	{
		free_lst_tok(&lst_tok);
		return (exec->exit[0]);
	}
	if (create_process(lst_proc, &lst_tok, &exec->exit[0]))
	{
		free_lst_tok(&lst_tok);
		free_lst_proc(lst_proc);
		return (exec->exit[0]);
	}
	free_lst_tok(&lst_tok);
	return (exec->exit[0]);
}
