/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:54:26 by rjobert           #+#    #+#             */
/*   Updated: 2023/10/12 16:54:29 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
search for the variable in the environment
and return the index if found, -1 otherwise
1. we extract the key part of key_value pair in our key=value
2. if this value isn't null we extratt the key of all env value
	and if one match -> we return it's index and free all extracted
	value (as come from ft_substring)
EXAMPLE : we look for USER, we iterate over each key_value pair 
and extrat characters before '=' (PWD, OLD_PWD, LANG,..) until we find 
USER and return it's index position
*/
int	search_env_var(char **env, char *target)
{
	int		i;
	char	*var_extract;

	if (!env)
		return (-1);
	i = 0;
	while (env && env[i])
	{
		var_extract = extract_variable(env[i]);
		if (var_extract)
		{
			if (!ft_strncmp(var_extract, target, ft_strlen(target) + 1))
			{
				free_pntr(var_extract);
				return (i);
			}
			free_pntr(var_extract);
		}
		i++;
	}
	return (-1);
}

/*
Finds the = sign in the key_value.
If the = is preceded by a +, it extracts the string before +=. Otherwise,
it extracts the string before =.
If no = sign is found, it returns NULL.
*/
char	*extract_variable(char *key_value)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (key_value[i])
	{
		if (key_value[i] == '=')
		{
			if (key_value[i - 1] && key_value[i - 1] == '+')
				len = i - 1;
			else
				len = i;
		}
		i++;
	}
	if (len == 0)
		return (NULL);
	return (ft_substr(key_value, 0, len));
}

/*
traverse key_value char * and return the substring of all characters
after the '=', if no '=' encountered return NULL
*/
char	*extract_value(char *key_value)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (key_value[i])
	{
		if (key_value[i] == '=')
			len = i + 1;
		i++;
	}
	if (len == 0)
		return (NULL);
	return (ft_substr(key_value, len, ft_strlen(key_value)));
}

char	**key_val_pair(char *str)
{
	char	**matrix;

	matrix = malloc(sizeof(char *) * 3);
	matrix[0] = extract_variable(str);
	matrix[1] = extract_value(str);
	matrix[2] = NULL;
	return (matrix);
}

void	free_key_val(char **kvp)
{
	int	i;

	if (!kvp || !*kvp)
		return ;
	i = 0;
	if (kvp)
	{
		while (kvp && kvp[i])
		{
			if (kvp[i])
			{
				free_pntr(kvp[i]);
				kvp[i] = NULL;
			}
			i++;
		}
	}
	free_pntr(kvp);
	kvp = NULL;
}
