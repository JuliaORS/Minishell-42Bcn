/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:17:43 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/04 20:19:55 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_env(char *str, int *i, int j, int *err)
{
	char	*str_bef_exp;
	char	*str_aft_exp;

	str_bef_exp = ft_substr(str, *i + 1, j);
	if (!str_bef_exp)
	{
		*err = 12;
		return (NULL);
	}
	str_aft_exp = getenv(str_bef_exp); //use our ft_getenv: separate malloc error or no path
	free(str_bef_exp);
	if (*err) //error with ft_getenv
		return (NULL);
	return (str_aft_exp);
}

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

char	*get_str_exp(char *str, int *i, int j, int *err)
{
	char	*str_aft_exp;
	char	*str_final;
	
	str_aft_exp = check_env(str, i, j, err);
	if (*err)
		return (NULL);
	str_final = create_new_str(str, str_aft_exp, i, j);
	if (!str_final)
	{
		if ((str_aft_exp))
			free(str_aft_exp);
		return (NULL);
	}
	return (str_final);
}

char	*check_expand(char *str, int *i, int *err)
{
	char	*str_final;
	int		j;

	j = 0;
	while (str[*i + 1 + j] && (ft_isalnum(str[*i + j + 1]) || \
		(str[*i + j + 1]) == '_'))
		j++;
	if (j != 0)
	{
		str_final = get_str_exp(str, i, j, err);
		if (!str_final)
			msg_error_parsing(12, err);
		free (str);
		return (str_final);
	}
	else
		return(str);
}

