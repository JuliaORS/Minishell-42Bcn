
#include "minishell.h"

int msg_error_parsing(int type, int *err)
{
    *err = type;
    if (type == 12)
         printf("minishell: Cannot allocate memory\n"); 
    else if (type == 258)
        printf("minishell: Syntax error near unexpected token `newline'\n"); 
    return (1);
}

