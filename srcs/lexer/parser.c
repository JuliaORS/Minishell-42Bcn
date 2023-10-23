/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:13:18 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/23 10:54:56 by julolle-         ###   ########.fr       */
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
		return (err_msg_parser(SYNTAX_MESS, 258, 1, exit));
	else
		*i = *i + (ft_strlen(line) - ft_strlen(pos)) + 1;
	return (0);
}

int	check_pipes(char *line, int *i, int *exit)
{
	int	j;

	j = 0;
	if (*i == 0 || !line[*i + 1] || line[*i + 1] == '|')
		return (err_msg_parser(SYNTAX_MESS, 258, '|', exit));
	while (j < *i)
	{
		if (line[j] != ' ')
			break ;
		j++;
	}
	if (j + 1 == *i)
		return (err_msg_parser(SYNTAX_MESS, 258, '|', exit));
	return (0);
}

int	check_redir(char *line, int *i, int *exit)
{
	if (line[*i] == '>' && line[*i + 1] && line[*i + 1] == '>')
		*i += 1;
	else if (line[*i] == '<' && line[*i + 1] && line[*i + 1] == '<')
		*i += 1;
	while (line[*i + 1] == ' ')
		*i += 1;
	if (!line[*i + 1])
		return (err_msg_parser(SYNTAX_MESS, 258, 1, exit));
	if (line[*i + 1] == '>' || line[*i + 1] == '<' || line[*i + 1] == '|')
		return (err_msg_parser(SYNTAX_MESS, 258, line[*i + 1], exit));
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
	if (str_is_empty(line))
		return (1);
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			check_quote(line + i + 1, &i, line[i], exit);
		else if (line[i] == '\\' && !line[i + 1])
			return (err_msg_parser(SYNTAX_MESS, 258, 1, exit));
		else if (line[i] == '>' || line[i] == '<')
			check_redir(line, &i, exit);
		else if (line[i] == '|')
			check_pipes(line, &i, exit);
		if (*exit)
			return (1);
		i++;
	}
	return (0);
}
