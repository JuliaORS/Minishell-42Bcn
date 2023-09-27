/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:52:12 by julolle-          #+#    #+#             */
/*   Updated: 2023/09/27 16:06:25 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	new_tok(t_tok **lst_tok, char *str, int type, int *exit_status)
{
	if (!str && type <= 2)
	{
		*exit_status = 1;
		return ;
	}	
	ft_lstadd_back_tok(lst_tok, ft_lstnew_tok(str, type, exit_status), exit_status);
}

int	create_tok_quote(t_tok **lst_tok, char *line, int *i, int type, int *exit_status)
{
	char	*pos;

	if (type == 0)
		pos = ft_strchr(line, '"');
	else
		pos = ft_strchr(line, '\'');
	if (type == 0)
		new_tok(lst_tok, ft_substr(line, 0, ft_strlen(line) - ft_strlen(pos)), 0, exit_status);
	else
		new_tok(lst_tok, ft_substr(line, 0, ft_strlen(line) - ft_strlen(pos)), 1, exit_status);
	*i = *i + (ft_strlen(line) - ft_strlen(pos)) + 1;
	return (0);
}

void	create_tok_redir(t_tok **lst_tok, char *line, int *i, int *exit_status)
{
	if (line[*i] == '>')
	{
		if (line[*i + 1] && line[*i + 1] == '>')
		{
			new_tok (lst_tok, NULL, 5, exit_status);
			*i += 1;
		}
		else
			new_tok(lst_tok, NULL, 4, exit_status);
	}
	else
	{
		if (line[*i + 1] && line[*i + 1] == '<')
		{
			new_tok (lst_tok, NULL, 7, exit_status);
			*i += 1;
		}
		else
			new_tok(lst_tok, NULL, 6, exit_status);
	}
}

void	create_tok_str(t_tok **lst_tok, char *line, int *i, int *exit_status)
{
	int	len;

	len = 0;
	while(line[len] != '"' && line[len] != '\'' && line[len] != '>' && line[len] != '<' && \
		line[len] != '|' && line[len] != ' ' && line[len] != '\\' && line[len] != '\0')
		len++;
	new_tok(lst_tok, ft_substr(line, 0, len), 2, exit_status);
	*i = *i + len - 1;
}

int	create_tok_slash(t_tok **lst_tok, char c, int *i, int *exit_status)
{
	char *str;

	str = malloc (sizeof(char) * 2);
	if (!str)
	{
		*exit_status = 1;
		return (1);
	}
	str[0] = c;
	str[1] = '\0';
 	new_tok(lst_tok, str, 2, exit_status);
	*i = *i + 1;
	return (0);
}

void	create_tok_space(t_tok **lst_tok, char *line, int *i, int *exit_status)
{
	int	len;

	len = 0;
	while (line[len] == ' ')
		len++;
	new_tok(lst_tok, NULL, 3, exit_status);
	*i = *i + len - 1;
}

int	create_tokens(t_tok **lst_tok, char *line, int *exit_status)
{
	int	i;

	i = 0;
	while (line[i] && !*exit_status)
	{
		if (line[i] == '"')
			create_tok_quote(lst_tok, line + i + 1, &i, 0, exit_status);
		else if (line[i] == '\'')
			create_tok_quote(lst_tok, line + i + 1, &i, 1, exit_status);
		else if (line[i] == '\\')
			create_tok_slash(lst_tok, line[i + 1], &i, exit_status);
		else if (line[i] == '>' || line[i] == '<')
			create_tok_redir(lst_tok, line, &i, exit_status);
		else if (line[i] == '|')
			new_tok(lst_tok, NULL, 8, exit_status);
		else if (line[i] == ' ')
			create_tok_space(lst_tok, line + i, &i, exit_status);
		else
			create_tok_str(lst_tok, line + i, &i, exit_status);
		i++;
	}
	expand_tokens(lst_tok);
	return (0);
}
