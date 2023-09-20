/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infile_outfile.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:56:05 by julolle-          #+#    #+#             */
/*   Updated: 2023/09/18 19:20:19 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *get_namefile(char *str)
{
	char    *file;
    
    while (*str == ' ')
		str++;
	if (str[0] == '"')
	{
		str++;
		file = ft_substr(str, 0, ft_strchr(str, '"') - str);
	}	
	else
		file = ft_substr(str, 0, ft_strchr(str, ' ') - str);	
    return (file);
}

void	find_infile(t_cmd *lst_cmd, char *process)
{
	char    *str;
	
    str = NULL;
	if (ft_strchr(process, '<'))
	{
		str = ft_strchr(process, '<');
		str++;
		if (*str == '<')
		{
			here_doc(lst_cmd, get_namefile(++str));
			lst_cmd->inf_status = 2;
		}
		else
        {
			lst_cmd->inf_status = 1;
		    lst_cmd->infile = get_namefile(str);
        }
    }
	else
		lst_cmd->inf_status = 0;
}

void find_outfile(t_cmd *lst_cmd, char *process)
{
	char    *str;
	
    str = NULL;
	if (ft_strchr(process, '>'))
	{
		str = ft_strchr(process, '>');
		str++;
		if (*str == '>')
		{
			lst_cmd->outf_status = 2;
			str++;
		}
		else
			lst_cmd->outf_status = 1;
        lst_cmd->outfile = get_namefile(str);
	}
	else
		lst_cmd->outf_status = 0;
}
