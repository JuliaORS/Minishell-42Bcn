# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 14:22:30 by julolle-          #+#    #+#              #
#    Updated: 2023/10/03 18:58:58 by julolle-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= libftprintf.a
HEADER      := ft_printf.h
SRC_DIR		:= src
SRCS		:= ft_printf.c ft_printhex.c ft_printnbr.c ft_printptr.c ft_printstr.c ft_printunbr.c

SRCS		:= $(SRCS:%=$(SRC_DIR)/%)

BUILD_DIR	:= .build
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS		:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.d)

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -MMD
AR			:= ar -rcs
RM			:= rm -f
DIR_DUP 	= mkdir -p $(@D)

# Implicit Method
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c	Makefile
	$(DIR_DUP)
	$(CC) $(CFLAGS) -I. -c -o $@ $<

# My methods
all:	$(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)
	$(info PRINTF compiled)

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

-include $(DEPS)

# My Ponny =)
.PHONY: all clean fclean re