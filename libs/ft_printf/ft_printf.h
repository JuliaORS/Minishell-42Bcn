/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:12:41 by rjobert           #+#    #+#             */
/*   Updated: 2023/05/23 16:46:42 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "../libft/libft.h"

int	ft_putchar(int c, int fd);
int	ft_putstr(char *s, int fd);
int	ft_print_nbr(int x, int fd);
int	ft_hexprint(unsigned int nb, int maj, int fd);
int	ft_print_ui(unsigned int n, int fd);
int	ft_print_ptr(void *ptr, int fd);
int	ft_printf(int fd, const char *s, ...);

#endif
