/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 12:45:30 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/15 13:08:55 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_no_space(char *str, int i, int j)
{
	char	*first_str;
	char	*sec_str;
	char	*final_str;

	first_str = ft_substr(str, 0, i + 1);
	if (!first_str)
		return (NULL);
	sec_str = ft_substr(str, i + j, ft_strlen(str) - i - j);
	if (!sec_str)
	{
		free(first_str);
		return (NULL);
	}
	final_str = ft_strjoin(first_str, sec_str);
	if (!final_str)
	{
		free(first_str);
		free(sec_str);
		return (NULL);
	}
	free(str);
	return (final_str);
}

char	*rem_space(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	new_str = ft_strtrim(str, " ");
	free(str);
	i = 0;
	j = 0;
	while (new_str[i])
	{
		if (new_str[i] == ' ')
		{
			j = 0;
			while (new_str[i + j] && new_str[i + j] == ' ')
				j++;
			if (j != 1)
			{
				new_str = str_no_space(new_str, i, j);
				i = i + j - 1;
			}
		}
		i++;
	}
	return (new_str);
}
