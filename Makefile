# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/03 17:22:44 by julolle-          #+#    #+#              #
#    Updated: 2023/08/03 17:22:44 by julolle-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell

HEADER      := minishell.h 

SRC_DIR		:= srcs
SRCS 		:= minishell.c list_tokens.c ft_lst_tokens.c list_process.c ft_lst_process.c
SRCS		:= $(SRCS:%=$(SRC_DIR)/%)

LIBFT_DIR 	:= includes/libft/
LIBFT		:= $(LIBFT_DIR)/libft.a

OBJS		:= $(SRCS:.c=.o)
DEPS		:= $(OBJS:.o=.d)

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -MMD 

RM			:= rm -f

#Implicit Method
%.o: %.c	Makefile $(LIBFT)
	$(CC) $(CFLAGS) -I ${HEADER} -c $< -o $@

# My methods
all:	subsystems $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) -lreadline -L $(LIBFT_DIR) -lft

subsystems:
	@make -s -C $(LIBFT_DIR)

clean:
	@$(RM) $(OBJS) $(DEPS)
	@make -s -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@make -s -C $(LIBFT_DIR) fclean

re:	fclean all

-include $(DEPS)

# Phony
.PHONY: all clean fclean re
