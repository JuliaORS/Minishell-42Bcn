/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:52:12 by julolle-          #+#    #+#             */
/*   Updated: 2023/09/28 14:50:01 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_tok(t_tok **lst_tok, char *str, int type, int *err)
{
	if (!str && type <= 2)
	{
		msg_error_parsing(12, err);
		return ;
	}
	ft_lstadd_back_tok(lst_tok, ft_lstnew_tok(str, type, err), err);
}

void	create_tok_quote(t_tok **lst_tok, char *line, int *i, int *err)
{
	char	*pos;

	if (line[*i] == '"')
	{
		pos = ft_strchr(line + 1, '"');
		new_tok(lst_tok, ft_substr(line, 0, ft_strlen(line) - ft_strlen(pos)), 0, err);
	}
	else
	{
		pos = ft_strchr(line, '\'');
		new_tok(lst_tok, ft_substr(line, 0, ft_strlen(line) - ft_strlen(pos)), 1, err);
	}
	*i = *i + (ft_strlen(line) - ft_strlen(pos)) + 2;
}

void	create_tok_redir(t_tok **lst_tok, char *line, int *i, int *err)
{
	if (line[*i] == '>')
	{
		if (line[*i + 1] && line[*i + 1] == '>')
		{
			new_tok (lst_tok, NULL, 5, err);
			*i += 1;
		}
		else
			new_tok(lst_tok, NULL, 4, err);
	}
	else
	{
		if (line[*i + 1] && line[*i + 1] == '<')
		{
			new_tok (lst_tok, NULL, 7, err);
			*i += 1;
		}
		else
			new_tok(lst_tok, NULL, 6, err);
	}
}

void	create_tok_str(t_tok **lst_tok, char *line, int *i, int *err)
{
	int	len;

	len = 0;
	while(line[len] != '"' && line[len] != '\'' && line[len] != '>' && line[len] != '<' && \
		line[len] != '|' && line[len] != ' ' && line[len] != '\\' && line[len] != '\0')
		len++;
	new_tok(lst_tok, ft_substr(line, 0, len), 2, err);
	*i = *i + len - 1;
}

int	create_tok_slash(t_tok **lst_tok, char c, int *i, int *err)
{
	char *str;

	str = malloc (sizeof(char) * 2);
	if (!str)
	{
		*err = 1;
		return (1);
	}
	str[0] = c;
	str[1] = '\0';
 	new_tok(lst_tok, str, 2, err);
	*i = *i + 1;
	return (0);
}

void	create_tok_space(t_tok **lst_tok, char *line, int *i, int *err)
{
	int	len;

	len = 0;
	while (line[len] == ' ')
		len++;
	new_tok(lst_tok, NULL, 3, err);
	*i = *i + len - 1;
}

int	create_tokens(t_tok **lst_tok, char *line, int *err)
{
	int	i;

	i = 0;
	while (line[i] && !*err)
	{
		if (line[i] == '"')
			create_tok_quote(lst_tok, line + i + 1, &i, err);
		else if (line[i] == '\'')
			create_tok_quote(lst_tok, line + i + 1, &i, err);
		else if (line[i] == '\\')
			create_tok_slash(lst_tok, line[i + 1], &i, err);
		else if (line[i] == '>' || line[i] == '<')
			create_tok_redir(lst_tok, line, &i, err);
		else if (line[i] == '|')
			new_tok(lst_tok, NULL, 8, err);
		else if (line[i] == ' ')
			create_tok_space(lst_tok, line + i, &i, err);
		else
			create_tok_str(lst_tok, line + i, &i, err);
		i++;
	}
	if (!*err)
		expand_tokens(lst_tok, err);
	//ft_print_list_tok(lst_tok);
	return (*err);
}
