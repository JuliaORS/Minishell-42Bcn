
#include "../../includes/minishell.h"

int main(int argc, char **argv, char **env)
{
	char	**arg;
	char	**dup_env;
	t_exec	exec;

	arg = NULL;
	if (argc > 1) 
	{
		arg = malloc(sizeof(char *) * (argc - 1));
		int i = -1;
		while (++i < argc - 1)
			arg[i] = argv[i + 1];
	}
	exec.env = env_dup(env);
	builtins(arg, &exec);
	//ft_env(exec.env, NULL);
	return (0);
}