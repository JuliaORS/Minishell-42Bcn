/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:19:03 by julolle-          #+#    #+#             */
/*   Updated: 2023/10/02 20:52:13 by julolle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

int		ft_printf(char const *str, ...);
int		ft_check_str(char const *str, va_list arg, int i, int res);
int		ft_idflag(char const flag, va_list arg);
int		ft_printchar(int chr);
int		ft_printstr(char *str);
int		ft_putptr(unsigned long long ptr);
int		ft_printptr(unsigned long long ptr);
int		ft_numlen(long long int num);
char	*ft_string(long long int n, char *s, int len);
char	*ft_litoa(long long int n);
int		ft_printnbr(int nbr);
int		ft_printunbr(unsigned int nbr);
int		ft_hexnumlen(unsigned long long num);
int		ft_print_hex_str(char *str);
int		ft_puthex(unsigned int nhex, const char flag);
int		ft_printhex( unsigned int nhex, const char flag);

#endif
