/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:09:22 by julolle-          #+#    #+#             */
/*   Updated: 2023/03/08 11:05:21 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countword(char const *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			word++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (word);
}

char	*fill_array(char const *s, char c, size_t *add_i, char *mat)
{
	int		j;
	int		let;
	size_t	i;

	j = 0;
	i = *add_i;
	let = 0;
	while (s[i + j] != c && s[i + j] != '\0')
		j++;
	mat = malloc(sizeof(char) * (j + 1));
	if (!mat)
		return (NULL);
	while (s[i] != c && s[i] != '\0')
	{
		mat[let] = s[i];
		i++;
		let++;
	}
	mat[let] = '\0';
	*add_i = i;
	return (mat);
}

int	protect_mat(char **mat, int wo)
{
	int	i;

	i = 0;
	if (!(mat[wo]))
	{
		while (i < wo)
		{
			free(mat[i]);
			i++;
		}
		free(mat);
		return (-1);
	}
	else
		return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	int		wo;
	char	**mat;

	i = 0;
	wo = 0;
	mat = malloc((sizeof(char *)) * (ft_countword(s, c) + 1));
	if (!mat)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			mat[wo] = fill_array(s, c, &i, mat[wo]);
			if (protect_mat(mat, wo) == -1)
				return (NULL);
			wo++;
		}
		else
			i++;
	}
	mat[wo] = NULL;
	return (mat);
}

/*int	main(void)
{
	char *s;
	char c;

	c = ' ';
	s = "hola1que1111tal11o1";
	ft_split("hello!zzzzzzzz", ' ');
	printf("%s", *ft_split(s, c));
}*/