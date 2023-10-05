/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:32:06 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/04 20:19:20 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_empty_token(t_tok **lst_tok, t_tok **start)
{
	t_tok	*tmp;
	t_tok	*tmp_space;
	
	tmp = *lst_tok;
	if ((*lst_tok)->prev && (*lst_tok)->next)
	{
		if ((*lst_tok)->prev->type == 3 && (*lst_tok)->next->type == 3 && (*lst_tok)->next->next)
		{
			tmp_space = (*lst_tok)->next;
			(*lst_tok)->prev->next = (*lst_tok)->next->next;
			(*lst_tok)->next->next->prev = (*lst_tok)->prev;
			(*lst_tok) = (*lst_tok)->prev;
			free(tmp_space);
		}
		else if ((*lst_tok)->prev->type == 3 && (*lst_tok)->next->type == 3 && !(*lst_tok)->next->next)
		{
			tmp_space = (*lst_tok)->next;
			(*lst_tok)->prev->next = NULL;
			free(tmp_space);
			(*lst_tok) = NULL;
		}
		else
		{	
			(*lst_tok)->prev->next = (*lst_tok)->next;
			(*lst_tok)->next->prev = (*lst_tok)->prev;
			(*lst_tok) = (*lst_tok)->prev;
		}
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
	if (tmp->str)
		free(tmp->str);
	free(tmp);
}

void	find_dollar_sign(t_tok **lst_tok, int *err)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while ((*lst_tok)->str[i])
	{
		if ((*lst_tok)->str[i] == '$')
		{
			(*lst_tok)->str = check_expand((*lst_tok)->str, &i, err);
			
			if (!(*lst_tok)->str)
				return ;
		}
		i++;
	}
}

void	skip_hd_str(t_tok **lst_tok)
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

void	expand_tokens(t_tok **lst_tok, int *err)
{
	t_tok	*tmp;

	tmp = *lst_tok;
	while (*lst_tok != NULL)
	{
		if ((*lst_tok)->type == 7)
			skip_hd_str(lst_tok);
		if ((*lst_tok) && ((*lst_tok)->type == 0 || (*lst_tok)->type == 2)) 
		{
			find_dollar_sign(lst_tok, err);
			if (ft_strlen((*lst_tok)->str) == 0)
				remove_empty_token(&(*lst_tok), &tmp);
		}
		if ((*lst_tok))
			(*lst_tok) = (*lst_tok)->next;
	}
	*lst_tok = tmp;
}
