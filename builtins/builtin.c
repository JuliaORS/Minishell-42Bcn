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

int main(int argc, char **argv, char **env)
{
	char **arg;
	t_env	*list;
	t_env	*head;

	arg = malloc(sizeof(char *) * (argc - 1));
	int i = -1;
	while (++i < argc - 1)
		arg[i] = argv[i + 1];
	list = list_env(env);
	head = list;
	// while (list)
	// {
	// 	printf("%s\n", list->var);
	// 	list = list->next;
	// }
	builtins(arg, list);
	free(arg);
	free_listenv(head);
	return (0);
}

void	builtins(char **arg, t_env *env)
{
	if (!ft_strncmp(arg[0], "cd", 3))
		ft_cd(arg);
	else if (!ft_strncmp(arg[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(arg[0], "echo", 5))
		ft_echo(arg);
	else if (!ft_strncmp(arg[0], "env", 5))
		ft_env(env, arg);
	else if (!ft_strncmp(arg[0], "export", 7))
		ft_export(&env, arg);
	
	// printf("TO CHECK THE MODIFY ENV");
	// char *quick_test[] = {"env", NULL};
	// ft_env(env, quick_test);
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
t_env	*list_env(char **env)
{
	int		i;
	t_env	*env_node;
	t_env	*list_env;


	if (!*env)
		return (NULL);
	i = -1;
	list_env = NULL;
	while (env[++i])
	{
		env_node = node_env(env[i]);
		if (!env_node)
		{
			free_listenv(list_env);
			return (NULL);
		}
		env_node->next = list_env;
		list_env = env_node;
	}
	return (list_env);
}

t_env	*node_env(char *s)
{
	t_env *env_node;
	
	env_node = malloc(sizeof(t_env));
	if (!env_node)
		return (NULL);
	env_node->var = s;
	env_node->next = NULL;
	return (env_node);
}

void	free_listenv(t_env *list)
{
	t_env	*tmp;

	if (!list)
		return;
	while(list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}

void	ft_env(t_env *env, char **arg)
{
	if (arg[1])
	{
		printf("env: %s: command not found\n", arg[1]);
		return ;
	}
	while(env)
	{
		printf("%s\n", env->var);
		env = env->next;
	}
	return ;
}

void	ft_export(t_env **head, char **arg)
{
		int		i;
		int		j;
		t_env	*env;

		if (!*head)
			return ;
		env = *head;
		if (!arg[1])
		{
			while(env)
			{
				printf("declare -x %s\n", env->var);
				env = env->next;
			}
			return ;
		}
		if (!ft_isalpha(arg[1][0]) && arg[1][0] != '_')
		{
			
			printf("minishell: export: `%s': not a valid identifier\n", arg[1]); //replace by official minishell name
			//printf("THUS %i\n", ft_isalpha(arg[1][0]));
			return ; 
		}
		i = 0;
		while (arg[1][++i])
			if (!ft_isalnum(arg[1][0]) && arg[1][0] != '_' && arg[1][0] != '=')
			{
				printf("minishell: export: `%s': not a valid identifier\n", arg[1]); //replace by official minishell name
				return ;
			}
		while (env->next)
			env = env->next;
		env->next = node_env(arg[1]); // SHOULD WE PROTECT MALLOC HERE IN CASE OUTOFMEM ?
}
