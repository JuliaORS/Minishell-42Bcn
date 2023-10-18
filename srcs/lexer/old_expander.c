/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:32:06 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/15 19:28:37 by julolle-         ###   ########.fr       */
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
		(*lst_tok) = (*lst_tok)->prev;
		(*lst_tok)->next = NULL;
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

char	*find_dollar_sign(char *str, t_exec *exec, int *end_pos, int *flag_exp)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] && str[i + 1] == '?')
				str = expand_error(str, &i, exec);
			else
			{
				str = check_expand(str, &i, exec);
				*flag_exp = 1;
			}
			if (!str)
				return (NULL);
			if ((size_t)i == ft_strlen(str) - 1)
				*end_pos = 1;
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

int	skip_exp(t_tok **lst_tok, int *end_pos)
{
	char	*new_str;
	
	new_str = ft_substr((*lst_tok)->prev->str, 0, ft_strlen((*lst_tok)->prev->str) - 1); 
	if (!new_str)
		return (1);
	free((*lst_tok)->prev->str);
	(*lst_tok)->prev->str = new_str;
	end_pos = 0;
	return (0);	
}


int	expand_tokens(t_tok **lst_tok, t_exec *exec)
{
	t_tok	*tmp;
	int		flag_exp;
	int		end_pos;
	
	end_pos = 0;
	tmp = *lst_tok;
	while (*lst_tok != NULL)
	{
		flag_exp = 0;
		if ((*lst_tok)->type == 7)
			skip_hdoc_str(lst_tok);
		else if (end_pos == 1 && (*lst_tok)->prev->type == 2  && \
			((*lst_tok)->type == 0||(*lst_tok)->type == 1))
		{
			if (skip_exp(lst_tok, &end_pos))
				return (msg_error_parsing(12, 0, &exec->exit[0]));
		}
		else if ((*lst_tok)->type == 0 || (*lst_tok)->type == 2)
		{
			end_pos = 0;
			(*lst_tok)->str = find_dollar_sign((*lst_tok)->str, exec, &end_pos, &flag_exp);
			if (!(*lst_tok)->str)
				return (msg_error_parsing(12, 0, &exec->exit[0]));
			if (ft_strlen((*lst_tok)->str) == 0 && flag_exp == 1)
				remove_empty_token(lst_tok, &tmp);
		}
		if ((*lst_tok))
			(*lst_tok) = (*lst_tok)->next;
	}
	*lst_tok = tmp;
	if (ft_lstsize_tok(*lst_tok) == 1 && (*lst_tok)->type == 3)
		return (1);

	return (exec->exit[0]);
}
