/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:06:32 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/12 15:45:07 by julolle-         ###   ########.fr       */
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
	if (line[*i] == '>' && line[*i + 1] && line[*i + 1] == '>')
		*i += 1;
	else if (line[*i] == '<' && line[*i + 1] && line[*i + 1] == '<')
		*i += 1;
	while (line[*i + 1] == ' ')
		*i += 1;
	if (!line[*i + 1])
		return (msg_error_parsing(258, 1, exit));
	else if ((line[*i + 1] == '>' || line[*i + 1] == '<') || \
		line[*i + 1] == '|')
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

int	manage_input(char *line, t_proc **lst_proc, t_exec *exec)
{
	t_tok	*lst_tok;

	lst_tok = NULL;
	if (parsing_input(line, &exec->exit[0]))
		return (1);
	if (create_tokens(&lst_tok, line, exec))
	{
		free_lst_tok(&lst_tok);
		return (1);
	}
	if (create_process(lst_proc, &lst_tok, &exec->exit[0]))
	{
		free_lst_tok(&lst_tok);
		free_lst_proc(lst_proc);
		return (1);
	}
	free_lst_tok(&lst_tok);
	return (0);
}
