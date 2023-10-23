/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:13:18 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/15 20:27:32 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *line, int *i, char qu, int *exit)
{
	char	*pos;

	if (qu == '"')
		pos = ft_strchr(line, '"');
	else
		pos = ft_strchr(line, '\'');
	if (!pos || (qu == '"' && line[ft_strlen(line) - \
		ft_strlen(pos) - 1] == '\\'))
		return (msg_error_parsing(258, 1, exit));
	else
		*i = *i + (ft_strlen(line) - ft_strlen(pos)) + 1;
	return (0);
}

int	check_redir_pipes(char *line, int *i, int *exit)
{
	int	tipo;

	if (line[*i] == '|')
		tipo = 1;
	if (line[*i] == '|' && *i == 0)
		return (msg_error_parsing(258, '|', exit));	
	if (line[*i] == '>' && line[*i + 1] && line[*i + 1] == '>')
		*i += 1;
	else if (line[*i] == '<' && line[*i + 1] && line[*i + 1] == '<')
		*i += 1;
	while (line[*i + 1] == ' ')
		*i += 1;
	if (!line[*i + 1])
		return (msg_error_parsing(258, 1, exit));
	if (tipo == 1 && line[*i + 1] == '|')
		return (msg_error_parsing(258, 1, exit));
	else if (tipo != 1 && (line[*i + 1] == '>' || line[*i + 1] == '<' || \
		line[*i + 1] == '|'))
		return (msg_error_parsing(258, line[*i + 1], exit));
	return (0);
}

int	str_is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	parsing_input(char *line, int *exit)
{
	int	i;

	i = 0;
	*exit = 0;
	if (str_is_empty(line))
		return (1);
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			check_quote(line + i + 1, &i, line[i], exit);
		else if (line[i] == '\\' && !line[i + 1])
			return (msg_error_parsing(258, 1, exit));
		else if (line[i] == '>' || line[i] == '<' || line[i] == '|')
			check_redir_pipes(line, &i, exit);
		if (*exit)
			return (1);
		i++;
	}
	return (0);
}
