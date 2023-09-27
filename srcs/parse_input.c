/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:06:32 by julolle-          #+#    #+#             */
/*   Updated: 2023/09/27 15:30:12 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_quote(char *line, int *i, char qu, int *exit_status)
{
	char	*pos;

	if (qu == '"')
		pos = ft_strchr(line, '"');
	else
		pos = ft_strchr(line, '\'');
	if (!pos || (qu == '"' && line[ft_strlen(line) - ft_strlen(pos) - 1] == '\\'))
		*exit_status = 258;
	else
		*i = *i + (ft_strlen(line) - ft_strlen(pos)) + 1;
}

void	check_slash(char c, int *exit_status)
{
	if (!c)
		*exit_status = 258;
}

void check_redir(char *line, int *i, int *exit_status)
{
	if (line[*i] == '>')
	{
		if (line[*i + 1] && line[*i + 1] == '>')
			*i += 1;
	}
	else
	{
		if (line[*i + 1] && line[*i + 1] == '<')
			*i += 1;
	}
	while (line[*i + 1] == ' ')
		*i += 1;
	if (!line[*i + 1] || line[*i + 1] == '|' || line[*i + 1] == '>' || line[*i + 1] == '<')
		*exit_status = 258;
}

void	check_pipe(char *line, int *i, int *exit_status)
{
	while (line[*i + 1] == ' ')
		*i += 1;
	if (!line[*i + 1])
		*exit_status = 258;
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

int	parsing_input(char *line, int *exit_status)
{
	int i;
	
	i = 0;
	*exit_status = 0;
	if (str_is_empty(line))
		return (1);
	while (line[i] && !*exit_status)
	{
		if (line[i] == '"' || line[i] == '\'')
			check_quote(line + i + 1, &i, line[i], exit_status);
		else if (line[i] == '\\')
			check_slash(line[i + 1], exit_status);
		else if (line[i] == '>' || line[i] == '<')
			check_redir(line, &i, exit_status);
		else if (line[i] == '|')
			check_pipe(line, &i, exit_status);	
		i++;
	}
	if (*exit_status)
	{
		free (line);
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}
