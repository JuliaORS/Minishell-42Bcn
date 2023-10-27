/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:15:32 by rjobert           #+#    #+#             */
/*   Updated: 2023/10/27 13:06:22 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
return current directory with sys function getcwd.
as the function behaviour (malloc or not memory) varies, 
we pass a NULL buffer in arguments and byte-size of 1056 to a buffer we are 
sure to be mallocated and free it later-on, so we ar sure to manage memory
correctly
*/
int	ft_pwd(t_exec *exec, char **arg)
{
	char	buffer[PATH_MAX];
	char	*backup;

	(void) arg;
	(void) exec;
	if (getcwd(buffer, PATH_MAX) != NULL)
	{
		ft_printf(STDOUT_FILENO, "%s\n", buffer);
		return (0);
	}
	else
	{
		backup = extract_value(ft_getenv(exec->env, "PWD"));
		ft_printf(STDOUT_FILENO, "%s\n", backup);
		if (backup)
			free(backup);
		return (0);
	}
	ft_printf(STDERR_FILENO, "Error finding current directory\n");
	return (1);
}
