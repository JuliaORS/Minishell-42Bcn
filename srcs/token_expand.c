/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:32:06 by julolle-          #+#    #+#             */
/*   Updated: 2023/09/28 13:44:05 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_str_exp(char *str, int *i, int j, int *err)
{
	char	*sub_str;
	char	*str_exp;
	char	*str_final;

	sub_str = ft_substr(str, *i + 1, j);
	if (!sub_str)
	{
		msg_error_parsing(12, err);
		return (NULL);
	}
	str_exp = getenv(sub_str); //utilitzar el nostre ft_getenv
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
	free(sub_str);
	return (str_final);
}

char	*check_expand(char *str, int *i, int *err)
{
	int		j;
	char	*str_final;

	str_final = str;
	j = 0;
	while (str[*i + 1 + j] && (ft_isalnum(str[*i + j + 1]) || (str[*i + j + 1]) == '_'))
		j++;
	if (j != 0)
	{
		str_final = get_str_exp(str, i, j, err);
		if (!str_final)
		{
			msg_error_parsing(12, err);
			return (NULL);
		}
	}
	free (str);
	return (str_final);
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
	free(tmp);
}

void	expand_tokens(t_tok **lst_tok, int *err)
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
					(*lst_tok)->str = check_expand((*lst_tok)->str, &i, err);
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
