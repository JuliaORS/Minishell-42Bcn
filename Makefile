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

SRC_PATH = ./srcs/
OBJ_PATH = ./objects/
INC_PATH = ./includes/

SRC		:= lexer/minishell.c lexer/parse_input.c lexer/token_list.c \
lexer/token_expand.c lexer/token_list_utils.c lexer/process_list.c \
lexer/process_list_utils.c lexer/print_free_list.c execution/exec_process.c \
execution/manage_process.c execution/pipes.c execution/utils_exec.c \
				builtins/builtin.c env/env_setup.c env/env_modify.c

SRCS		:= $(addprefix $(SRC_PATH), $(SRC))

LIBFT_DIR 	:= $(addprefix $(INC_PATH), libft)
LIBFT		:= $(LIBFT_DIR)/libft.a

OBJS		:= $(addprefix $(OBJ_PATH), $(SRC:.c=.o))
DEPS		:= $(addprefix $(OBJ_PATH), $(OBJS:.o=.d))
INC	=  -I $(addprefix $(INC_PATH), $(HEADER))
CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -MMD 

RM			:= rm -f

#Implicit Method
$(OBJ_PATH)%.o: $(SRC_PATH)%.c	Makefile $(LIBFT)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# My methods
all: subsystems $(NAME)

-include $(DEPS)
$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) -lreadline -L $(LIBFT_DIR) -lft

subsystems:
	@make -s -C $(LIBFT_DIR)

# $(OBJ_PATH):
# 	mkdir -p $(OBJ_PATH)
# 	mkdir -p $(OBJ_PATH)/lexer

clean:
	@$(RM) $(OBJS) $(DEPS)
	@$(RM) -rf $(OBJ_PATH)
	@make -s -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@make -s -C $(LIBFT_DIR) fclean

re:	fclean all


# Phony
.PHONY: all clean fclean re
