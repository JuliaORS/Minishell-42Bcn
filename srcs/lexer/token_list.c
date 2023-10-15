/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:52:12 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/15 12:00:33 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_tok_quote(t_tok **lst_tok, char *line, int *i, int *exit)
{
	char	*pos;
	char	*sub_str;

	if (line[0] == '"')
	{
		pos = ft_strchr(line + 1, '"');
		sub_str = ft_substr(line, 1, ft_strlen(line) - ft_strlen(pos) - 1);
	}
	else
	{
		pos = ft_strchr(line + 1, '\'');
		sub_str = ft_substr(line, 1, ft_strlen(line) - ft_strlen(pos) - 1);
	}
	if (!sub_str)
		return (msg_error_parsing(12, 0, exit));
	if (new_tok(lst_tok, sub_str, 0, exit))
		return (1);
	*i = *i + (ft_strlen(line) - ft_strlen(pos));
	return (0);
}

void	create_tok_redir(t_tok **lst_tok, char *line, int *i, int *exit)
{
	if (line[*i] == '>' && line[*i + 1] && line[*i + 1] == '>')
	{
		if (new_tok (lst_tok, NULL, 5, exit))
			return ;
		*i += 1;
	}
	else if (line[*i] == '>')
	{
		if (new_tok (lst_tok, NULL, 4, exit))
			return ;
	}
	else if (line[*i] == '<' && line[*i + 1] && line[*i + 1] == '<')
	{
		if (new_tok (lst_tok, NULL, 7, exit))
			return ;
		*i += 1;
	}
	else if (line[*i] == '<')
	{
		if (new_tok (lst_tok, NULL, 6, exit))
			return ;
	}
}

int	create_tok_str(t_tok **lst_tok, char *line, int *i, int *exit)
{
	int		len;
	char	*str;

	len = 0;
	while (line[len] != '"' && line[len] != '\'' && line[len] != '>' && \
		line[len] != '<' && line[len] != '|' && line[len] != ' ' && \
		line[len] != '\0')
		len++;
	str = ft_substr(line, 0, len);
	if (!str)
		return (msg_error_parsing(12, 0, exit));
	if (new_tok(lst_tok, str, 2, exit))
		return (1);
	*i = *i + len - 1;
	return (0);
}

void	create_tok_space(t_tok **lst_tok, char *line, int *i, int *exit)
{
	int	len;

	len = 0;
	while (line[len] == ' ')
		len++;
	if (new_tok(lst_tok, NULL, 3, exit))
		return ;
	*i = *i + len - 1;
}

int	create_tokens(t_tok **lst_tok, char *line, t_exec *exec)
{
	int	i;

	i = 0;
	while (line[i] && !exec->exit[0])
	{
		if (line[i] == '"' || line[i] == '\'')
			create_tok_quote(lst_tok, line + i, &i, &exec->exit[0]);
		else if (line[i] == '>' || line[i] == '<')
			create_tok_redir(lst_tok, line, &i, &exec->exit[0]);
		else if (line[i] == '|')
			new_tok(lst_tok, NULL, 8, &exec->exit[0]);
		else if (line[i] == ' ')
			create_tok_space(lst_tok, line + i, &i, &exec->exit[0]);
		else
			create_tok_str(lst_tok, line + i, &i, &exec->exit[0]);
		i++;
	}
	if (!exec->exit[0])
		exec->exit[0] = expand_tokens(lst_tok, exec);
	return (exec->exit[0]);
}
