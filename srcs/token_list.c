/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:52:12 by julolle-          #+#    #+#             */
/*   Updated: 2023/09/26 18:32:36 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	new_tok(t_tok **lst_tok, char *str, int type)
{
	ft_lstadd_back_tok(lst_tok, ft_lstnew_tok(str, type));
}

int	create_tok_quot(t_tok **lst_tok, char *line, int *i, int type)
{
	char	*pos;

	if (type == 0)
		pos = ft_strchr(line, '"'); //pending manage \"
	else
		pos = ft_strchr(line, '\'');
	if (!pos || (type == 0 && line[ft_strlen(line) - ft_strlen(pos) - 1] == '\\'))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		exit(258); //ERROR 258 ->unexpected token
	}
	if (type == 0)
		new_tok(lst_tok, ft_substr(line, 0, ft_strlen(line) - ft_strlen(pos)), 0);
	else
		new_tok(lst_tok, ft_substr(line, 0, ft_strlen(line) - ft_strlen(pos)), 1);
	*i = *i + (ft_strlen(line) - ft_strlen(pos)) + 1;
	return (0);
}

void	create_tok_redir(t_tok **lst_tok, char *line, int *i)
{
	if (line[*i] == '>')
	{
		if (line[*i + 1] && line[*i + 1] == '>')
		{
			new_tok (lst_tok, NULL, 5);
			*i += 1;
		}
		else
			new_tok(lst_tok, NULL, 4);
	}
	else
	{
		if (line[*i + 1] && line[*i + 1] == '<')
		{
			new_tok (lst_tok, NULL, 7);
			*i += 1;
		}
		else
			new_tok(lst_tok, NULL, 6);
	}
}

void	create_tok_str(t_tok **lst_tok, char *line, int *i)
{
	int	len;

	len = 0;
	while(line[len] != '"' && line[len] != '\'' && line[len] != '>' && line[len] != '<' && \
		line[len] != '|' && line[len] != ' ' && line[len] != '\\' && line[len] != '\0')
		len++;
	new_tok(lst_tok, ft_substr(line, 0, len), 2);
	*i = *i + len - 1;
}

void	create_tok_slash(t_tok **lst_tok, char c, int *i)
{
	char *str;

	str = malloc (sizeof(char) * 2);
	if (!c)
	{
		printf("minishell: syntax error near unexpected token `newline'\n assa");
		exit(258); //ERROR 258 ->unexpected token
	}
	else
	{
		str[0] = c;
		str[1] = '\0';
 		new_tok(lst_tok, str, 2);
		*i = *i + 1;
	}
}

void	create_tok_space(t_tok **lst_tok, char *line, int *i)
{
	int	len;

	len = 0;
	while (line[len] == ' ')
		len++;
	new_tok(lst_tok, NULL, 3);
	*i = *i + len - 1;
}

int	create_tokens(t_tok **lst_tok, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
			create_tok_quot(lst_tok, line + i + 1, &i, 0); //mirar error
		else if (line[i] == '\'')
			create_tok_quot(lst_tok, line + i + 1, &i, 1); //mirar error
		else if (line[i] == '\\')
			create_tok_slash(lst_tok, line[i + 1], &i);
		else if (line[i] == '>' || line[i] == '<')
			create_tok_redir(lst_tok, line, &i);
		else if (line[i] == '|')
			new_tok(lst_tok, NULL, 8);
		else if (line[i] == ' ')
			create_tok_space(lst_tok, line + i, &i);
		else
			create_tok_str(lst_tok, line + i, &i);
		i++;
	}
	expand_tokens(lst_tok);
	return (0);
}
