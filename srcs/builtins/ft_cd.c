
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

#include "minishell.h"

void    update_env_dir(t_exec *exec, char *old_path, char **arg);
char    *extract_path(char *keyvalue);
void    check_set_pwd(t_exec *exec, char **curr_dir, char **curr_path, char **arg);

/*
checking that the path leads to a correct directoy
1. check that the path leads to a directory with opendir() and exit if error
2. check that the file name is not bigger than 1 byte
3. check with access that the path exist (F_OK) and if so 
that we have access rights (X_OK) and display corresponding error messages
4. check that the path endpoint is a directory (combining stat and S_ISDIR)
*/
int check_directory(const char *path)
{
    struct stat path_info;

    if (ft_strlen(path) > FILE_MAX) 
    {
        ft_printf(STDERR_FILENO, "minishell: cd: %s: File name too long\n", path);
        return (1);
    }
    if (stat(path, &path_info) < 0)
    {
        ft_printf(STDERR_FILENO, "minishell: cd: %s: No such file or directory\n", path);
        return (1);
    }
    if (!S_ISDIR(path_info.st_mode))
    {
        ft_printf(STDERR_FILENO, "minishell: cd: %s: Not a directory\n", path);
        return (1);
    }
    if (access(path, X_OK) < 0)
    {
        ft_printf(STDERR_FILENO, "minishell: cd: %s: Permission denied\n", path);
        return (1);
    }
    return (0);
}

/*
actual cd buitlins : 
first we savet the current directory to update OLDPWD later on
case with no arguments going to HOME var :
    1. we extract HOME=XXXX from env and get the path (part after =)
    2. if chdir return issue -> error message
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
    if (arg[1] && arg[1][0] == '\0')
        return (0);
    if (!arg[1])
    {
        if (chdir(extract_path(ft_getenv(exec->env, "HOME"))) == -1)
        {
		    ft_printf(STDERR_FILENO, "cd: HOME not set\n");
            return (1);
        }
    }
    else if (check_directory(arg[1]))
        return (1) ;
    else if (chdir(arg[1]) != 0)
    {
		ft_printf(STDERR_FILENO, "cd: %s\n", arg[1]); 
        return (1);
    }
    update_env_dir(exec, old_path, arg);
    exec->dir_init = 1;
    return (0);
}

/*
from old_path (saved before applying chdir()) and then using getcwd(), add
prefix PWD or OLDPWD to old and new path and replace the corresponding index in 
the environment
*/
void    update_env_dir(t_exec *exec, char *old_path, char **arg)
{
    char *curr_dir;
    char *curr_path;

    curr_dir = getcwd(NULL, PATH_MAX);
    if (!old_path)
        old_path = curr_dir;
    old_path = ft_strjoin("OLD", old_path);
    check_set_pwd(exec, &curr_dir, &curr_path, arg);
    if (exec->dir_init == 0)
        exec->env = realloc_env(exec->env, old_path);
    else
        replace_env_var(exec->env, "OLDPWD", old_path);
    free_pntr(old_path);
    return ;
}

void    check_set_pwd(t_exec *exec, char **curr_dir, char **curr_path, char **arg)
{
    char *reset_pwd;

    if (!*curr_dir)
    {
        reset_pwd = ft_strjoin("/", arg[1]);
        replace_env_var(exec->env, "PWD", ft_strjoin(ft_getenv(exec->env, "PWD"),reset_pwd));
        free(reset_pwd);
        ft_printf(STDERR_FILENO, "cd: error retrieving current directory:" 
        " getcwd: cannot access parent directories: No such file or directory\n");
    }
    else
    {
        *curr_path = ft_strjoin("PWD=", *curr_dir);
        replace_env_var(exec->env, "PWD", *curr_path);
        free_pntr(*curr_dir);
        free_pntr(*curr_path);
    }
    return;
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