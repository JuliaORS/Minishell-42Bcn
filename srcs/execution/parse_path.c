/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:42:40 by rjobert           #+#    #+#             */
/*   Updated: 2023/10/10 16:42:42 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 Extract the PATH from environment variables in env[]
 1 - we receive env from the command line, it is array of char*
 if it is null (env empty), we return a matrix split of a default path
 2 - else we itetrate over each env[x] while not null, iterate while first
 four chars are different than "PATH"
 3 - when we found it, we return it minus the 5 first char (that are "PATH=")
 4 - if there an is no path in the env (extremely rare but this is 42 school...)
 we replace it by a pre-define PATH in the header
*/
char	**search_path(char *env[])
{
	int		i;
	char	**path_matrix;
	char	*path;

	path = NULL;
	i = 0;
	if (!env || !*env)
		return (NULL) ; //Careful this is pipex modified for no environment
	else
	{
		while (env[i] && ft_strncmp(env[i], "PATH", 4))
			i++;
		if (env[i])
			path = env[i] + 5;
	}
	path_matrix = ft_split(path, ':');
	return (path_matrix);
}

/* 
now let's look for a command line function in the path and 
return the path exec 
 1 - we iterate over all path (if there are some) and
 use strjoin to to first go from cmd (like cat) to a
 cmd path (like /cat) and use strjoin again on a potential path
 2 - we free free the path_cmd and we now use the access function 
 to check if path/cmd  (like /bin/cat) exist with F_OK. 
 3 - if it does, we return (and free in another function) else
 we free and move to next potential from in all_path 
 */
char	*exec_path(char **all_path, t_proc *exec_trgt)
{
	char	*test_path;
	char	*temp_cmd;
	char	*cmd;

	if (!all_path)
		return (NULL);
	cmd = exec_trgt->arg[0];
	while (*all_path)
	{
		temp_cmd = ft_strjoin("/", cmd);
		test_path = ft_strjoin(*all_path, temp_cmd);
		free(temp_cmd);
		if (access(test_path, F_OK) == 0)
			return (test_path);
		free(test_path);
		all_path++;
	}
	return (NULL);
}

/* for the special case of a relative path ./subfoler/path
there can be weird test like :
 ./script\"quote.sh that is correct in shell but execve can not
 accept the escape character (\) in path nor command so we
 need to clean both and end-up with ./script"quote.sh 
 (which woulld be wrong for cdl but correct for execve)
 */
void	relative_path_clean(t_proc **proc,  t_exec **exec)
{
	int	i;

	if (!*proc|| !*exec)
		return ;
	if (ft_strchr((*proc)->arg[0], 32))
		error_msg(CMNF_MESS, CMNOFOUND, *exec, *proc);
	i = 0;
	while ((*proc)->arg[i])
	{
		if (ft_strnstr((*proc)->arg[i], "\"", ft_strlen((*proc)->arg[i])))
			ft_strtrim((*proc)->arg[i], "\\");
		if (ft_strnstr((*proc)->arg[i], "\'", ft_strlen((*proc)->arg[i])))
			ft_strtrim((*proc)->arg[i], "\\");
		i++;
	}
	if (ft_strnstr((*exec)->path, "\"", ft_strlen((*exec)->path)))
		(*exec)->path = (*proc)->arg[0];
	if (ft_strnstr((*exec)->path, "\'", ft_strlen((*exec)->path)))
		(*exec)->path = (*proc)->arg[0];
}
