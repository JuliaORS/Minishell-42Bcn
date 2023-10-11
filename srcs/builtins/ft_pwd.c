/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:15:32 by rjobert           #+#    #+#             */
/*   Updated: 2023/09/25 12:15:35 by rjobert          ###   ########.fr       */
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
	char *buffer;

	(void) arg;
	(void) exec;
	buffer = getcwd(NULL, 1056);
	if (buffer != NULL)
	{
		printf("%s\n", buffer);
		free(buffer);
		return (0);
	}
	perror("Error finding current directory");
	return (1);
}