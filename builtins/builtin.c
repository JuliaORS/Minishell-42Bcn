/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:15:32 by rjobert           #+#    #+#             */
/*   Updated: 2023/09/25 12:15:35 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

// int main(int argc, char **argv, char **env)
// {
// 	char	**arg;
// 	char	**dup_env;
// 	t_exec	exec;

// 	arg = NULL;
// 	if (argc > 1)
// 	{
// 		arg = malloc(sizeof(char *) * (argc - 1));
// 		int i = -1;
// 		while (++i < argc - 1)
// 			arg[i] = argv[i + 1];
// 	}
// 	exec.env = env_dup(env);
// 	builtins(arg, &exec);
// 	ft_env(exec.env, NULL);
// 	return (0);
// }

void	builtins(char **arg, t_exec *exec)
{
	if (!arg)
		return ;
	if (!ft_strncmp(arg[0], "cd", 3))
		ft_cd(arg);
	else if (!ft_strncmp(arg[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(arg[0], "echo", 5))
		ft_echo(arg);
	else if (!ft_strncmp(arg[0], "env", 5))
		ft_env(exec->env, arg);
	else if (!ft_strncmp(arg[0], "export", 7))
		ft_export(exec, arg);
}

void	ft_pwd(void)
{
	char buffer[1024];
	if (getcwd(buffer, sizeof(buffer)) != NULL)
		printf("%s\n", buffer);
	else	
		printf("%s\n",strerror(errno));
}
 
void	ft_cd(char **arg)
{
	char *home_path;

	if (arg[1])
	{
		if (chdir(arg[1]))
			printf("%s %s: %s\n","cd:",strerror(errno), arg[1]);
	}
	else
	{	
		//home_path = ft_getenv("$HOME");
		chdir("$HOME");
	}
}

/*
	receive arguments array and execute eco-liek function
	1. if second argument is not -n, execute echo on all following
		value in array of args until it is NULL. 
	2. if second argument is -n -> flag value is 1 and no trailing nl
		and array of words to echo start one value after in the 
		array of arguments. words are separated by a space until the 
		last word
*/
void	ft_echo(char **arg)
{
	int	i;
	int	flag;

	if (arg[1])
	{
		if (!ft_strncmp(arg[1], "-n", 3))
		{
			i = 2;
			flag = 1;
		}
		else 
		{
			i = 1;
			flag = 0;
		}
	}
	while (arg[i])
	{
		printf("%s", arg[i++]);
		if (arg[i])
			printf(" ");
	}
	if (flag == 1)
		return ;
	printf("\n");
}

/*
converting the env array to a list (for export builtin)
front insertion
*/
// t_env	*list_env(char **env)
// {
// 	int		i;
// 	t_env	*env_node;
// 	t_env	*list_env;


// 	if (!*env)
// 		return (NULL);
// 	i = -1;
// 	list_env = NULL;
// 	while (env[++i])
// 	{
// 		env_node = node_env(env[i]);
// 		if (!env_node)
// 		{
// 			free_listenv(list_env);
// 			return (NULL);
// 		}
// 		env_node->next = list_env;
// 		list_env = env_node;
// 	}
// 	return (list_env);
// }

// t_env	*node_env(char *s)
// {
// 	t_env *env_node;
	
// 	env_node = malloc(sizeof(t_env));
// 	if (!env_node)
// 		return (NULL);
// 	env_node->var = s;
// 	env_node->next = NULL;
// 	return (env_node);
// }

// void	free_listenv(t_env *list)
// {
// 	t_env	*tmp;

// 	if (!list)
// 		return;
// 	while(list)
// 	{
// 		tmp = list->next;
// 		free(list);
// 		list = tmp;
// 	}
// }

void	ft_env(char **env, char **arg)
{
	int	i;

	if (arg && arg[1])
	{
		printf("env: %s: command not found\n", arg[1]);
		return ;
	}
	i = 0;
	while(env && env[i] && i < count_var_env(env))
	{
		printf("%s\n", env[i]);
		i++;
	}
	return ;
}

int	ft_export(t_exec *exec, char **arg)
{
		int		i;
		int		idx;

		if (!exec->env)
			return (0);
		i = -1;
		if (!arg[1])
		{
			while(exec->env && exec->env[++i])
				printf("declare -x %s\n", exec->env[i]);
			return (0);
		}
		if (!check_syntax_export(arg[1]))
			return (0);
		idx = search_env_var(exec->env, arg[1]);
		if (idx == -1 )
			exec->env = realloc_mem_env(exec->env, arg[1]);
		else
		{
			i = 0;
			while(arg[1][i] != '=')
				i++;
			free(exec->env[i]);
			exec->env[i] = ft_substr(arg[1], i, ft_strlen(arg[1]));
			if (!exec->env[i]) //HANDLE MALLOC DEEEPER HERE
				return (-1);
		}
		return (0);
}

int	check_syntax_export(char *var)
{
	int	i;
	int	valid;

	if (!var)
		return (0);
	if (!ft_isalpha(var[0]) && var[0] != '_')
	{
		printf("minishell: export: `%s': not a valid identifier\n", var); //replace by official minishell name
		return (0);
	}
	i = -1;
	valid = 0;
	while(var[++i])
		if (var[i] == '=')
			valid = 1;
	if (valid == 0)
		return (0);
	i = -1;
	while (var[++i] && var[i] != '=')
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
	return (1);
}