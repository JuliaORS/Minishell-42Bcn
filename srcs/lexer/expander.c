/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:32:06 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/15 12:01:46 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rem_prev_next(t_tok **lst_tok)
{
	t_tok	*tmp_space;

	if ((*lst_tok)->prev->type == 3 && (*lst_tok)->next->type == 3 && \
		(*lst_tok)->next->next)
	{
		tmp_space = (*lst_tok)->next;
		(*lst_tok)->prev->next = (*lst_tok)->next->next;
		(*lst_tok)->next->next->prev = (*lst_tok)->prev;
		(*lst_tok) = (*lst_tok)->prev;
		free(tmp_space);
	}
	else if ((*lst_tok)->prev->type == 3 && (*lst_tok)->next->type == 3 && \
		!(*lst_tok)->next->next)
	{
		tmp_space = (*lst_tok)->next;
		(*lst_tok)->prev->next = NULL;
		(*lst_tok) = NULL;
		free(tmp_space);
	}
	else
	{
		(*lst_tok)->prev->next = (*lst_tok)->next;
		(*lst_tok)->next->prev = (*lst_tok)->prev;
		(*lst_tok) = (*lst_tok)->prev;
	}
}

void	remove_empty_token(t_tok **lst_tok, t_tok **start)
{
	t_tok	*tmp;

	tmp = *lst_tok;
	if ((*lst_tok)->prev && (*lst_tok)->next)
		rem_prev_next(lst_tok);
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
	if (tmp->str)
		free(tmp->str);
	free(tmp);
}

char	*find_dollar_sign(char *str, t_exec *exec, int mode)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?' && mode == 0)
				str = expand_error(str, &i, exec);
			else
				str = check_expand(str, &i, exec);
			if (!str)
				break ;
		}
		i++;
	}
	return (str);
}

void	skip_hdoc_str(t_tok **lst_tok)
{
	if ((*lst_tok)->next && ((*lst_tok)->next->type <= 2 || \
		((*lst_tok)->next->type == 3 && (*lst_tok)->next->next && \
		(*lst_tok)->next->next->type <= 2)))
	{
		(*lst_tok) = (*lst_tok)->next;
		if ((*lst_tok)->type == 3)
			(*lst_tok) = (*lst_tok)->next;
		while ((*lst_tok)->next && (*lst_tok)->type <= 2)
			(*lst_tok) = (*lst_tok)->next;
		if ((*lst_tok)->type <= 2)
			(*lst_tok) = (*lst_tok)->next;
	}
}

int	expand_tokens(t_tok **lst_tok, t_exec *exec)
{
	t_tok	*tmp;

	tmp = *lst_tok;
	while (*lst_tok != NULL)
	{
		if ((*lst_tok)->type == 7)
			skip_hdoc_str(lst_tok);
		else if ((*lst_tok)->type == 0 || (*lst_tok)->type == 2)
		{
			(*lst_tok)->str = find_dollar_sign((*lst_tok)->str, exec, 0);
			if (!(*lst_tok)->str)
			{
				msg_error_parsing(12, 0, &exec->exit[0]);
				return (exec->exit[0]);
			}
			if (ft_strlen((*lst_tok)->str) == 0)
				remove_empty_token(lst_tok, &tmp);
		}
		if ((*lst_tok))
			(*lst_tok) = (*lst_tok)->next;
	}
	*lst_tok = tmp;
	return (exec->exit[0]);
}
