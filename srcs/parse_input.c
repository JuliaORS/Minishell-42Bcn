/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:06:32 by julolle-          #+#    #+#             */
/*   Updated: 2023/09/28 14:38:20 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quote(char *line, int *i, char qu, int *err)
{
	char	*pos;

	if (qu == '"')
		pos = ft_strchr(line, '"');
	else
		pos = ft_strchr(line, '\'');
	if (!pos || (qu == '"' && line[ft_strlen(line) - ft_strlen(pos) - 1] == '\\'))
		msg_error_parsing(258, err);
	else
		*i = *i + (ft_strlen(line) - ft_strlen(pos)) + 1;
}

void check_redir_pipes(char *line, int *i, int *err)
{
	if (line[*i] == '>' && line[*i + 1] && line[*i + 1] == '>')
			*i += 1;
	else if (line[*i] == '<' && line[*i + 1] && line[*i + 1] == '<')
			*i += 1;
	while (line[*i + 1] == ' ')
		*i += 1;
	if (!line[*i + 1] || line[*i + 1] == '|')
		*err = 258;
	if	((line[*i] == '>' || line[*i] == '<') && (line[*i + 1] == '>' || line[*i + 1] == '<'))
		msg_error_parsing(258, err);
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

int	parsing_input(char *line, int *err)
{
	int i;
	
	i = 0;
	if (str_is_empty(line))
		return (1);
	while (line[i] && !*err)
	{
		if (line[i] == '"' || line[i] == '\'')
			check_quote(line + i + 1, &i, line[i], err);
		else if (line[i] == '\\' && !line[i + 1])
			*err = 258;
		else if (line[i] == '>' || line[i] == '<' || line[i] == '|')
			check_redir_pipes(line, &i, err);
		i++;
	}
	if (*err)
		free(line);
	return (0);
}


int	manage_input(char *line, t_proc **lst_proc, int *err)
{
	t_tok	*lst_tok;

	lst_tok = NULL;
	(void)lst_proc; //OJO!!
	*err = 0;
	if (parsing_input(line, err))
		return (1);
	if (create_tokens(&lst_tok, line, err))
		return (1);
	if (create_process(lst_proc, &lst_tok, err))
		return (1);
	return (0);
}