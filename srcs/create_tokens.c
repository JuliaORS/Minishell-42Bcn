/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:52:12 by julolle-          #+#    #+#             */
/*   Updated: 2023/09/20 14:50:09 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void new_tok(t_tok **lst_tok, char *str, int type)
{
	ft_lstadd_back_tok(lst_tok, ft_lstnew_tok(str, type));
}

int	create_tok_quot(t_tok **lst_tok, char *line, int *i, int type)
{
	char	*pos;
	int		j;
	int		k;
	int		l;

	l = 0;
	k = 0;
	j = 0;
	while(j <= *i)
	{
		line++;
		j++;
	}
	if (type == 0)
		pos = ft_strchr(line, '\''); //pending manage \"
	else
		pos = ft_strchr(line, '"');
	if (pos == 0)
		return (-1); //ERROR
	if (type == 0)
		new_tok(lst_tok, ft_substr(line, 0, ft_strlen(line) - ft_strlen(pos)), 0);
	else
		new_tok(lst_tok, ft_substr(line, 0, ft_strlen(line) - ft_strlen(pos)), 1);
	*i = *i + (ft_strlen(line) - ft_strlen(pos));
	return (0);
}

void	create_tok_redir(t_tok **lst_tok, char *line, int *i)
{
	if (line[*i] == '>')
	{
		if (line[*i+1] && line[*i+1] == '>')
		{
			new_tok (lst_tok, NULL, 5);
			*i+=1;
		}
		else
			new_tok(lst_tok, NULL, 4);
	}
	else
	{
		if (line[*i+1] && line[*i+1] == '<')
		{
			new_tok (lst_tok, NULL, 7);
			*i+=1;
		}
		else
			new_tok(lst_tok, NULL, 6);
	}
}

void	create_tok_str(t_tok **lst_tok, char *line, int *i)
{
	int	len;
	
	len = 0;
	while(line[len] != '\'' && line[len] != '>' && line[len] != '<' && \
		line[len] != '|' && line[len] != ' ' && line[len] != '\0')
		len++;
	new_tok(lst_tok, ft_substr(line, 0, len), 2);
	*i = *i + len-1;
}
void create_tok_space(t_tok **lst_tok, char *line, int *i)
{
	int	len;
	
	len = 0;
	while(line[len] == ' ')
		len++;
	new_tok(lst_tok, NULL, 3);
	*i = *i + len-1;
}

int	create_tokens(t_tok **lst_tok, char *line)
{
	int	i;

	i = 0;
	while(line[i])
	{
		if (line[i] == '\'')
			create_tok_quot(lst_tok, line, &i, 0); //mirar error
		else if (line[i] == '"')
			create_tok_quot(lst_tok, line, &i, 1); //mirar error
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
	return (0);
}

void free_lst(t_tok *lst_tok)
{
	while (lst_tok)
	{
		free(lst_tok);
		lst_tok = lst_tok->next;
	}
}

void	ft_print_list(t_tok *lst_tok)
{
	while (lst_tok != NULL)
	{
		printf("string: %s // type: %i\n", lst_tok->str, lst_tok->type);
		lst_tok = lst_tok->next;
	}
	free_lst(lst_tok);
}
