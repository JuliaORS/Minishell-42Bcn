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

SRC		:= lexer/minishell.c lexer/parse_input.c lexer/token_list.c \
lexer/token_expand.c lexer/token_list_utils.c lexer/process_list.c \
lexer/process_list_utils.c lexer/print_free_list.c execution/exec_process.c \
execution/manage_process.c execution/pipes.c execution/utils_exec.c \
				builtins/builtin.c env/env_setup.c env/env_modify.c

SRCS		:= $(addprefix $(SRC_PATH), $(SRC))

PRINTF_DIR  := includes/ft_printf/
PRINTF		:= $(PRINTF_DIR)/libftprintf.a

RLINE_DIR 	:= includes/readline/
RLINE		:= $(RLINE_DIR)/libreadline.a
RLINE_H		:= $(RLINE_DIR)/libhistory.a

LIB_FLAGS	:= -lreadline -ltermcap -lft -lftprintf

OBJS		:= $(SRCS:.c=.o)
DEPS		:= $(OBJS:.o=.d)

OBJS		:= $(addprefix $(OBJ_PATH), $(SRC:.c=.o))
DEPS		:= $(addprefix $(OBJ_PATH), $(OBJS:.o=.d))
INC	=  -I $(addprefix $(INC_PATH), $(HEADER))
CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -MMD 

RM			:= rm -f

#Implicit Method
%.o: %.c	Makefile $(LIBFT) $(RLINE) $(RLINE_H) $(PRINTF)
	$(CC) $(CFLAGS) -I ${INCLUDES} -c $< -o $@

# My methods
all: subsystems $(NAME)

-include $(DEPS)
$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) $(RLINE_H) $(RLINE) $(LIB_FLAGS) -L $(LIBFT_DIR) -L $(PRINTF_DIR) 
	$(info MINISHELL compiled)

subsystems:
	@make -s -C $(LIBFT_DIR)
	@make -s -C $(RLINE_DIR) 
	@make -s -C $(PRINTF_DIR)

# $(OBJ_PATH):
# 	mkdir -p $(OBJ_PATH)
# 	mkdir -p $(OBJ_PATH)/lexer

clean:
	@$(RM) $(OBJS) $(DEPS)
	@$(RM) -rf $(OBJ_PATH)
	@make -s -C $(LIBFT_DIR) clean
	@make -s -C $(PRINTF_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@make -s -C $(LIBFT_DIR) fclean
	@make -s -C $(PRINTF_DIR) fclean

re:	fclean all


# Phony
.PHONY: all clean fclean re
