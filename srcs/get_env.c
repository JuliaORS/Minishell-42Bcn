/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:57:41 by julolle-          #+#    #+#             */
/*   Updated: 2023/09/18 15:57:57 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**search_path(char *env[])
{
	int		i;
	char	**path_matrix;
	char	*path;

	path = NULL;
	i = 0;
	if (!env || !*env)
	{
		path_matrix = ft_split(DEF_PATH, ':');
		return (path_matrix);
	}
	else
	{
		while (env[i] && ft_strncmp(env[i], "PATH", 4))
			i++;
		if (env[i])
			path = env[i] + 5;
		else
			path = DEF_PATH;
	}
	path_matrix = ft_split(path, ':');
	return (path_matrix);
}

char	*exec_path(char **all_path, char *cmd)
{
	char	*test_path;
	char	*tmp_cmd;

	if (!all_path)
		return (NULL);
	while (*all_path)
	{
		tmp_cmd = ft_strjoin("/", cmd);
		test_path = ft_strjoin(*all_path, tmp_cmd);
		free(tmp_cmd);
		if (access(test_path, F_OK) == 0)
			return (test_path);
		free(test_path);
		all_path++;
	}
	return (NULL);
}
