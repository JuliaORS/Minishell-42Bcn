/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:45:27 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/04 15:41:12 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msg_error_parsing(int type, int *err)
{
	*err = type;
	if (type == 12)
		printf("minishell: Cannot allocate memory\n");
	else if (type == 258)
		printf("minishell: Syntax error near unexpected token `newline'\n");
	return (0);
}
