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

INCLUDES      := includes/

SRC_DIR		:= srcs
SRCS 		:= minishell.c parse_input.c token_list.c token_expand.c \
				token_expand_str.c token_list_utils.c process_list.c \
				process_list_utils.c print_free_list.c error_parsing.c \
				signals.c heredoc.c \
				
SRCS		:= $(SRCS:%=$(SRC_DIR)/%)

LIBFT_DIR 	:= includes/libft/
LIBFT		:= $(LIBFT_DIR)/libft.a

PRINTF_DIR  := includes/ft_printf/
PRINTF		:= $(PRINTF_DIR)/libftprintf.a

RLINE_DIR 	:= includes/readline/
RLINE		:= $(RLINE_DIR)/libreadline.a
RLINE_H		:= $(RLINE_DIR)/libhistory.a

LIB_FLAGS	:= -lreadline -ltermcap -lft -lftprintf

OBJS		:= $(SRCS:.c=.o)
DEPS		:= $(OBJS:.o=.d)

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -MMD 

RM			:= rm -f

#Implicit Method
%.o: %.c	Makefile $(LIBFT) $(RLINE) $(RLINE_H) $(PRINTF)
	$(CC) $(CFLAGS) -I ${INCLUDES} -c $< -o $@

# My methods
all:	subsystems $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) $(RLINE_H) $(RLINE) $(LIB_FLAGS) -L $(LIBFT_DIR) -L $(PRINTF_DIR) 
	$(info MINISHELL compiled)

subsystems:
	@make -s -C $(LIBFT_DIR)
	@make -s -C $(RLINE_DIR) 
	@make -s -C $(PRINTF_DIR)

clean:
	@$(RM) $(OBJS) $(DEPS)
	@make -s -C $(LIBFT_DIR) clean
	@make -s -C $(PRINTF_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@make -s -C $(LIBFT_DIR) fclean
	@make -s -C $(PRINTF_DIR) fclean

re:	fclean all

-include $(DEPS)

# Phony
.PHONY: all clean fclean re
