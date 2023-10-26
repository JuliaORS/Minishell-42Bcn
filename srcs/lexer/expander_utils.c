/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:10:04 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/26 11:17:50 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_final_str(char *str_exp, char *beg_str, char *end_str, int *i)
{
	char	*mid_str;
	char	*final_str;

	if (!str_exp)
	{
		final_str = ft_strjoin(beg_str, end_str);
		*i = *i - 1;
	}
	else
	{
		mid_str = ft_strjoin(str_exp, end_str);
		if (!mid_str)
			return (NULL);
		final_str = ft_strjoin(beg_str, mid_str);
		*i = *i + ft_strlen(str_exp) - 1;
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
	char	*str_exp_var;
	char	*str_aft_exp;
	char	*str_final;

	str_bef_exp = ft_substr(str, *i + 1, j);
	if (!str_bef_exp)
		return (NULL);
	str_exp_var = ft_getenv(exec->env, str_bef_exp);
	if (str_exp_var)
		str_aft_exp = extract_value(str_exp_var);
	else
	{
		str_aft_exp = malloc (sizeof(char) * 1);
		if (str_aft_exp)
			str_aft_exp[0] = '\0';
	}
	free(str_bef_exp);
	if (!str_aft_exp)
		return (NULL);
	str_final = create_new_str(str, str_aft_exp, i, j);
	free(str_aft_exp);
	return (str_final);
}

char	*check_expand(char *str, int *i, t_exec *exec, int *flag_exp)
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
		*flag_exp = 1;
		free(str);
		return (new_str);
	}
	else
		return (str);
}

char	*expand_num_null(char *str, int *i)
{
	char	*str_final;

	str_final = create_new_str(str, NULL, i, 1);
	free(str);
	return (str_final);
}
