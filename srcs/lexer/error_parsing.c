/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:45:27 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/15 14:59:06 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_error(t_exec *exec)
{
	if (g_exit_sig)
		exec->exit[1] = g_exit_sig;
	else
		exec->exit[1] = exec->exit[0];
	exec->exit[0] = 0;
	g_exit_sig = 0;
}

int	msg_error_parsing(int type, int ch, int *exit)
{
	*exit = type;
	if (type == 12)
		ft_printf(STDERR_FILENO, "minishell🦄: Cannot allocate memory hola\n");
	else if (type == 258 && ch == 1)
		ft_printf(STDERR_FILENO, "minishell🦄: syntax error near unexpected token `newline'\n");
	else if (type == 258 && ch != 1)
		ft_printf(STDERR_FILENO, "minishell🦄: syntax error near unexpected token `%c'\n", ch);
	return (type);
}
