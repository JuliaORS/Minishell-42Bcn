
#include "../../includes/minishell.h"

void    update_env_dir(t_exec *exec, char *old_path);
char    *extract_path(char *keyvalue);

/*
checking that the path leads to a correct directoy
1. check with access that the path exist (F_OK) and we have access rights (X_OK)
    and display corresponding error messages
2. check that the path endpoint is a directory (combining stat and S_ISDIR)
*/
int check_directory(const char *path)
{
    struct stat info;

    if (access(path,F_OK) == -1)
    {
        perror("cd: no such file or directory: REPLACE_WITH_DIR\n"); // replace by ft_printf()
        return (1);
    }
    if (access(path, X_OK) == -1)
    {
        perror("cd: REPLACE_WITH_DIR: Permission denied\n"); // replace by ft_printf()
        return (1);
    }
    if (stat(path, &info) == 0)
    {
        if (!S_ISDIR(info.st_mode))
        {
            perror("cd : REPLACE_W_DIR: Not a directory\n");
            return (1);
        }
    }
    return (0);
}

/*
actual cd buitlins : 
case with no arguments going to HOME var :
    1. we extract HOME=XXXX from env and get the path (part after =)
    2. if chdir return issue -> error messafe
case with arguments
    1. check that the path is correct with function check_directory
    2. go to the directory and return error if issue with chdir()
then update the PWD and OLDPWD part of the current env with function 
update_env_dir

*/
int    ft_cd(t_exec *exec, char **arg)
{
    char *old_path;

	old_path = ft_getenv(exec->env, "PWD");
    if (!arg[1])
    {
        if (chdir(extract_path(ft_getenv(exec->env, "HOME"))) == -1)
        {
		    perror("cd: "); //relace with ft_printf
            return (1);
        }
    }
    else
    {
        if (check_directory(arg[1]))
            return (1) ;
        if (chdir(arg[1]) == -1)
        {
		    perror("cd: REPLACE_WITH_arg[1]\n"); //relace with ft_printf
            return (1);
        }
    }
    update_env_dir(exec, old_path);
    return (0);
}

/*
from old_path (saved before applying chdir()) and then using getcwd(), add
prefix PWD or OLDPWD to old and new path and replace the corresponding index in 
the environment
*/
void update_env_dir(t_exec *exec, char *old_path)
{
    char *curr_dir;
    char *curr_path;

    old_path = ft_strjoin("OLD", old_path);
    curr_dir = getcwd(NULL, 1056);
    curr_path = ft_strjoin("PWD=", curr_dir);
    free(curr_dir);
    replace_env_var(exec->env, "OLDPWD", old_path);
    replace_env_var(exec->env, "PWD", curr_path);
    free(curr_path);
    free(old_path);
    return ;
}

char *extract_path(char *keyvalue)
{
    int i;

    if (!keyvalue)
        return (NULL);
    i = 0;
    while (keyvalue[i] != '=')
        i++;
    return (ft_substr(keyvalue, i + 1, ft_strlen(keyvalue)));   
}