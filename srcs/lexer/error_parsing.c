/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:45:27 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/23 10:49:58 by julolle-         ###   ########.fr       */
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

void	update_error(t_exec *exec)
{
	if (g_exit_sig)
		exec->exit[0] = g_exit_sig;
}

int	err_msg_parser(char *msg, int type, int ch, int *exit)
{
	*exit = type;
	if (type == 12)
		ft_printf(STDERR_FILENO, "minishell: %s\n", msg);
	else if (type == 258 && ch == 1)
		ft_printf(STDERR_FILENO, "minishell: %s `newline'\n", msg);
	else if (type == 258 && ch != 1)
		ft_printf(STDERR_FILENO, "minishell: %s `%c'\n", msg, ch);
	return (type);
}
