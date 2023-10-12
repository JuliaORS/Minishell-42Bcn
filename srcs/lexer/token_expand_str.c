/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:17:43 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/10 17:49:41 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *create_final_str(char *str_aft_exp, char *beg_str, char *end_str, int *i)
{
	char	*mid_str;
	char	*final_str;
	
	if (!str_aft_exp)
	{
		final_str = ft_strjoin(beg_str, end_str);
		*i = *i - 1;
	}
	else
	{
		mid_str = ft_strjoin(str_aft_exp, end_str);
		if (!mid_str)
			return (NULL);
		final_str = ft_strjoin(beg_str, mid_str);
		*i = *i + ft_strlen(str_aft_exp) - 1;
		free(mid_str);
	}
	return (final_str);
}

char	*create_new_str(char *str, char *str_aft_exp, int *i, int j)
{
	char	*beg_str;
	char	*end_str;
	char	*final_str;
	
	beg_str = ft_substr(str, 0, *i);
	if (!beg_str)
		return (NULL);
	end_str = ft_substr(str, *i + 1 + j, ft_strlen(str) - *i - j);
	if (!end_str)
	{	
		free(beg_str);
		return (NULL);
	}
	final_str = create_final_str(str_aft_exp, beg_str, end_str, i);
	free(beg_str);
	free(end_str);
	return (final_str);
}

char	*get_str_exp(char *str, int *i, int j, t_exec *exec)
{
	char	*str_bef_exp;
	char	*str_aft_exp;
	char	*str_final;
	
	(void)exec; //borrar despres;
	str_bef_exp = ft_substr(str, *i + 1, j);
	if (!str_bef_exp)
		return (NULL);
	//str_aft_exp = ft_getenv(exec->env, str_bef_exp); //use our ft_getenv: separate malloc error or no path
	str_aft_exp = getenv(str_bef_exp);
	free(str_bef_exp);
	str_final = create_new_str(str, str_aft_exp, i, j);
	//if (str_aft_exp)
		//free(str_aft_exp); //use our ft_getenv: separate malloc error or no path
	return (str_final);
}

char	*check_expand(char *str, int *i, t_exec *exec)
{
	char	*new_str;
	int		j;

	j = 0;
	while (str[*i + 1 + j] && (ft_isalnum(str[*i + j + 1]) || \
		(str[*i + j + 1]) == '_'))
		j++;
	if (j != 0)
	{
		new_str = get_str_exp(str, i, j, exec);
		free (str);
		return (new_str);
	}
	else
		return(str);
}
