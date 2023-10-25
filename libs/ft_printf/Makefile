# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/17 14:23:19 by rjobert           #+#    #+#              #
#    Updated: 2023/10/25 13:40:52 by julolle-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEF_COLOR	:=	\033[1;97m
CIAN		:=	\033[1;96m

CC = cc
CFLAGS = -Wall -Werror -Wextra
HEADER = ft_printf.h
SRC = ft_printf.c ft_print_nbr.c ft_putchar.c ft_uitoa.c ft_hexprint.c \
	  ft_print_ptr.c ft_putstr.c
OBJS = $(SRC:.c=.o)
NAME = libftprintf.a
LIB_PATH = ../libft
LIBFT = $(LIB_PATH)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	cp $(LIBFT) $(NAME)
	ar -rcs $(NAME) $(OBJS)
	@echo "$(CIAN)PRINTF compiled$(DEF_COLOR)"

$(LIBFT):
	make -C $(LIB_PATH) all 

%.o: %.c  $(HEADER)
	$(CC) -c $(CFLAGS) -I ./ $< -o $@  


fclean: clean
	make -C $(LIB_PATH) fclean
	rm -rf $(NAME)	

clean:
	rm -f $(OBJS)
	make -C $(LIB_PATH) clean

re: fclean all

.PHONY: all clean fclean re
