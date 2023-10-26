/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:52:12 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/26 11:25:10 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_tok_quote(t_tok **lst_tok, char *line, int *i, t_exec *exec)
{
	char	*pos;
	char	*str;

	if (remove_dol_end(lst_tok, &exec->exit[0]))
		return (exec->exit[0]);
	pos = ft_strchr(line + 1, line[0]);
	str = ft_substr(line, 1, ft_strlen(line) - ft_strlen(pos) - 1);
	if (!str)
		return (err_msg_parser(MALLOC_MESS, 12, 0, &exec->exit[0]));
	*i = *i + (ft_strlen(line) - ft_strlen(pos));
	if (line[0] == '"' && ft_strlen(str) == 0)
		new_tok(lst_tok, str, 0, &exec->exit[0]);
	else if (line[0] == '"' && ft_strlen(str) != 0)
		expander(lst_tok, str, exec, 0);
	else
		new_tok(lst_tok, str, 1, &exec->exit[0]);
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

int	create_tok_str(t_tok **lst_tok, char *line, int *i, t_exec *exec)
{
	int		len;
	char	*str;
	char	*str_exp;

	len = 0;
	while (line[len] != '"' && line[len] != '\'' && line[len] != '>' && \
		line[len] != '<' && line[len] != '|' && line[len] != ' ' && \
		line[len] != '\0')
		len++;
	*i = *i + len - 1;
	str = ft_substr(line, 0, len);
	if (!str)
		return (exec->exit[0]);
	str_exp = expander(lst_tok, str, exec, 2);
	if (!str_exp)
		return (exec->exit[0]);
	if (ft_strlen(str_exp) == 0)
		free(str_exp);
	if (str_exp[ft_strlen(str_exp) - 1] == ' ' && (line[len] == '"' \
		|| line[len] == '\''))
		new_tok(lst_tok, NULL, 3, &exec->exit[0]);
	return (0);
}

void	create_tok_space(t_tok **lst_tok, char *line, int *i, int *exit)
{
	int	len;

	len = 0;
	while (line[len] == ' ' || line[len] == '\0')
		len++;
	if (new_tok(lst_tok, NULL, 3, exit))
		return ;
	*i = *i + len - 1;
}

int	create_tokens(t_tok **lst_tok, char *input, t_exec *exec)
{
	int		i;
	char	*line;

	i = 0;
	line = ft_strtrim(input, " ");
	while (line[i] && !exec->exit[0])
	{
		if (line[i] == '"' || line[i] == '\'')
			create_tok_quote(lst_tok, line + i, &i, exec);
		else if (line[i] == '>' || line[i] == '<')
			create_tok_redir(lst_tok, line, &i, &exec->exit[0]);
		else if (line[i] == '|')
			new_tok(lst_tok, NULL, 8, &exec->exit[0]);
		else if (line[i] == ' ')
			create_tok_space(lst_tok, line + i, &i, &exec->exit[0]);
		else
			create_tok_str(lst_tok, line + i, &i, exec);
		i++;
	}
	free(line);
	if (ft_lstsize_tok(*lst_tok) == 1 && (*lst_tok)->type == 3)
		return (1);
	return (exec->exit[0]);
}
