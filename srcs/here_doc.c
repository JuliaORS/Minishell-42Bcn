/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:08:01 by julolle-          #+#    #+#             */
/*   Updated: 2023/09/18 18:24:15 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*strch_join(char *s1, char c)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s1)
	{
		str = malloc(sizeof(char) * 2);
		if (!str)
			return (NULL);
	}
	else
	{
		str = malloc(sizeof(char) * ft_strlen(s1) + 1 + 1);
		if (!str)
			return (NULL);
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
	}
	str[i++] = c;
	str[i] = '\0';
	return (str);
}

int	get_next_line_hd(int fd, char **line)
{
	char		c;
	int			rd;

	*line = NULL;
	rd = 1;
	while (1)
	{
		rd = read(fd, &c, 1);
		if (rd < 0)
		{
			write(1, "Error\n", 6);
			return (-1);
		}
		if (rd == 0)
			break ;
		*line = strch_join(*line, c);
		if (c == '\n')
			break ;
	}
	if (rd == 0)
		return (0);
	return (1);
}

void	here_doc(t_cmd *lst_cmd, char *eof)
{
	int		file;
	char	*buf;

	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		write (1, "Error\n", 6); //manage Errors
	while (1)
	{
		write(1, "heredoc> ", 9);
		if (get_next_line_hd(0, &buf) <= 0)
			write (1, "Error\n", 6); //manage Errors
		if (!ft_strncmp(eof, buf, ft_strlen(eof)))
			break ;
		write(file, buf, ft_strlen(buf));
	}
	free(buf);
	close(file);
	file = open(".heredoc_tmp", O_RDONLY);
	if (file  < 0)
	{
		unlink(".heredoc_tmp");
		write(1, "Error\n", 6); //manage Errors
	}
    lst_cmd->infile = ".heredoc_tmp";
}
