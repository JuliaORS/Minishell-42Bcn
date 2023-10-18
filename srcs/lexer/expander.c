/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:09:34 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/18 15:51:18 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_dollar_sign(char *str, t_exec *exec, int *end_pos, int *flag_exp)
{
	int		i;
	//char	*tmp;
	
	
	(void)end_pos;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] && str[i + 1] == '?')
				str = expand_error(str, &i, exec);
			else
			{
				
				str = check_expand(str, &i, exec, flag_exp);
			}
			if (!str)
				return (NULL);
		}
		i++;
	}
	return (str);
}

int skip_hdoc(t_tok **lst_tok)
{
	t_tok   *tmp;
	
	if (!(*lst_tok))
		return (0);
	tmp = ft_lstlast_tok(*lst_tok);
	while (tmp && tmp->type <= 2)
		tmp = tmp->prev;
	if (tmp && tmp->type == 7)
		return (1);
	else if (tmp && tmp->type == 3 && tmp->prev && tmp->prev->type == 7)
	   return (1);
	return (0);
}

char	*expander(t_tok **lst_tok, char *str, t_exec *exec, int *flag_exp)
{
	char	*str_exp;
	int		end_pos;

	end_pos = 0; // treure
	if (skip_hdoc(lst_tok))
		return (str);
	str_exp = find_dollar_sign(str, exec, &end_pos, flag_exp);
	
	return (str_exp);
}