
#include "../../includes/minishell.h"

void	builtins(char **arg, t_exec *exec)
{
	if (!arg)
		return ;
	if (!ft_strncmp(arg[0], "cd", 3))
		ft_cd(exec, arg);
	else if (!ft_strncmp(arg[0], "pwd", 4))
		ft_pwd(exec, arg);
	else if (!ft_strncmp(arg[0], "echo", 5))
		ft_echo(exec, arg);
	else if (!ft_strncmp(arg[0], "env", 5))
		ft_env(exec, arg);
	else if (!ft_strncmp(arg[0], "export", 7))
		ft_export(exec, arg);
	//else if (!ft_strncmp(arg[0], "unset", 6))
	//	ft_unset(exec, arg);
}

int main(int argc, char **argv, char **env)
{
	char	**arg;
	char	**dup_env;
	int i;
	t_exec	exec;

	arg = NULL;
	if (argc > 1) 
	{
		arg = malloc(sizeof(char *) * (argc));
		i = -1;
		while (++i < argc - 1)
			arg[i] = argv[i + 1];
	}
	arg[i] = NULL;
	exec.env = env_dup(env);
	ft_env(&exec, NULL);
	builtins(arg, &exec);
	printf("\n\n\n ============ now after the unset ======== \n\n\n");
	ft_env(&exec, NULL);
	return (0);
}