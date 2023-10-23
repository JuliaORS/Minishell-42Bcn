/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:30:00 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/23 10:52:06 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_mat(char **mat)
{
	int i;

	i = 1;
	while (mat[i])
	{
		free(mat[i]);
		i++;
	}
	free(mat);
}

int	add_new_tok_exp(t_tok **lst_tok, char *str, int *exit)
{
	int		wo;
	int		num_words;
	char	**mat_str;

	num_words = 0;
	wo = 0;
	mat_str = ft_split(str, ' ');
	if (!mat_str)
		return (err_msg_parser(MALLOC_MESS, 12, 0, exit));
	while (mat_str[num_words])
		num_words++;
	while (mat_str[wo] != NULL && *exit == 0)
	{	
		new_tok(lst_tok, ft_strdup(mat_str[wo]), 2, exit);
		if (wo < num_words - 1)
			new_tok(lst_tok, NULL, 3, exit);
		wo++;
	}
	free_mat(mat_str);
	return (0);
}


int	split_tok(t_tok **lst_tok, char *str, int *exit)
{
	t_tok	*tmp;

	tmp = ft_lstlast_tok(*lst_tok);
	if (str[0] == ' ' && tmp && tmp->type <= 1)
	{	
		if (new_tok(lst_tok, NULL, 3, exit))
			return (1);
	}
	add_new_tok_exp(lst_tok, str, exit);
	return (0);
}
