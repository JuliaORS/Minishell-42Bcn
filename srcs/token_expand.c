/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:32:06 by julolle-          #+#    #+#             */
/*   Updated: 2023/09/26 15:57:01 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_expand(char *str, int *i)
{
	int		j;
	char	*str_exp;
	char	*str_final;

	str_final = str;
	j = 0;
	while (str[*i + 1 + j] && (ft_isalnum(str[*i + j + 1]) || (str[*i + j + 1]) == '_'))
			j++;
	if (j != 0)
	{
		str_exp = getenv(ft_substr(str, *i + 1, j)); //utilitzar el nostre ft_getenv
		if (!str_exp)
		{
			str_final = ft_strjoin(ft_substr(str, 0, *i), ft_substr(str, \
				*i + 1 + j, ft_strlen(str) - *i - j));
			*i = *i - 1;
		}
		else
		{	
			str_final = ft_strjoin(ft_substr(str, 0, *i), ft_strjoin(str_exp, \
				ft_substr(str, *i + 1 + j, ft_strlen(str) - *i - j)));
			*i = *i + ft_strlen(str_exp) - 1;
		}
	}
	return (str_final);
}

void	free_node_tok(t_tok *node_tok)
{
	free(node_tok);
}

void	remove_token(t_tok **lst_tok, t_tok **start)
{
	t_tok	*tmp;

	tmp = *lst_tok;
	if ((*lst_tok)->prev && (*lst_tok)->next)
	{
		(*lst_tok)->prev->next = (*lst_tok)->next;
		(*lst_tok)->next->prev = (*lst_tok)->prev;
		(*lst_tok) = (*lst_tok)->next;
	}
	else if ((*lst_tok)->prev && !((*lst_tok)->next))
	{
		(*lst_tok)->prev->next = NULL;
		(*lst_tok) = NULL;
	}
	else if (!(*lst_tok)->prev && ((*lst_tok)->next))
	{
		(*lst_tok) = (*lst_tok)->next;
		(*lst_tok)->prev = NULL;
		*start = (*lst_tok);
	}
	else
	{
		(*lst_tok) = NULL;
		*start = NULL;
	}
	free_node_tok(tmp);
}

void	expand_tokens(t_tok **lst_tok)
{
	int		i;
	t_tok	*tmp;

	tmp = *lst_tok;
	while (*lst_tok != NULL)
	{
		if ((*lst_tok)->type == 0 || (*lst_tok)->type == 2)
		{
			i = 0;
			while ((*lst_tok)->str[i])
			{
				if ((*lst_tok)->str[i] == '$')
					(*lst_tok)->str = check_expand((*lst_tok)->str, &i);
				i++;
			}
			if (ft_strlen((*lst_tok)->str) == 0)
				remove_token(&(*lst_tok), &tmp);
		}
		if ((*lst_tok))
			(*lst_tok) = (*lst_tok)->next;
	}
	*lst_tok = tmp;
}
