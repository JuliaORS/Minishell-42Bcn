/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:30:00 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/18 16:07:37 by julolle-         ###   ########.fr       */
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

void	add_new_tok_exp(t_tok **lst_tok, char *str, int *exit)
{
	char	**mat_str;
	int		wo;
	int		num_words;

	num_words = 0;
	wo = 0;
	mat_str = ft_split(str, ' ');

	while (mat_str[num_words])
		num_words++;
	while (mat_str[wo] != NULL)
	{	
		new_tok(lst_tok, ft_strdup(mat_str[wo]), 2, exit);
		if (wo < num_words - 1)
		{
			new_tok(lst_tok, NULL, 3, exit);
		}
		wo++;
	}
	free_mat(mat_str);
}


int	sep_tok(t_tok **lst_tok, char *str, int *exit)
{
	t_tok   *tmp;

	int 	len;
	//int		flag_end;
	
	//flag_end = 0;
	tmp = ft_lstlast_tok(*lst_tok);
	//afegir espai al principi
	if (str[0] == ' ' && tmp && tmp->type <= 1)
	{	
		if (new_tok(lst_tok, NULL, 3, exit))
			return (1);  //manage error 
	}
	add_new_tok_exp(lst_tok, str, exit);
	//afegir espai al final flag!!!
	len = (ft_strlen((*lst_tok)->str)) - 1;

	return (0);
}
