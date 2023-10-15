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

NAME        = minishell
HEADER      = ./includes/
SRC_PATH    = srcs/
SRC         = lexer/minishell.c lexer/parse_input.c lexer/token_list.c \
            lexer/token_expand.c lexer/token_expand_str.c lexer/token_list_utils.c \
            lexer/process_list.c lexer/process_list_files.c \
			      lexer/process_list_utils.c lexer/print_free_list.c \
            lexer/error_parsing.c lexer/signals.c lexer/heredoc.c \
            execution/exec_process.c execution/manage_process.c \
            execution/pipes.c execution/utils_exec.c execution/parse_path.c \
            builtins/ft_cd.c builtins/ft_echo.c builtins/ft_export.c \
            builtins/ft_pwd.c builtins/ft_unset.c builtins/ft_exit.c \
            env/env_setup.c env/env_modify.c env/env_search.c 
SRCS        = $(addprefix $(SRC_PATH), $(SRC))
LIBFT_PATH  = includes/libft/
LIBFT       = $(LIBFT_PATH)/libft.a
PRINTF_PATH = includes/ft_printf/
PRINTF      = $(PRINTF_PATH)/libftprintf.a
RLINE_PATH  = includes/readline/
RLINE       = $(RLINE_PATH)/libreadline.a
RLINE_H     = $(RLINE_PATH)/libhistory.a
LIB_FLAGS   = -lreadline -ltermcap -lft -lftprintf
OBJ_PATH    = ./OBJ/
OBJ         = $(addprefix $(OBJ_PATH), $(SRC:.c=.o))
DEP         = $(addprefix $(OBJ_PATH), $(OBJ:.o=.d))
INC         = -I$(addprefix $(INC_PATH), $(HEADER))
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -MMD 
RM          = rm -f
#Implicit Method

$(OBJ_PATH)%.o: $(SRC_PATH)%.c Makefile $(LIBFT) $(RLINE) $(RLINE_H) $(PRINTF)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@
# My methods

all: $(OBJ_PATH) subsystems $(NAME)

-include $(DEP)
$(NAME):  $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(RLINE_H) $(RLINE) $(LIB_FLAGS) -L $(LIBFT_PATH) -L $(PRINTF_PATH) 
	$(info MINISHELL compiled)

subsystems:
	@make -s -C $(LIBFT_PATH)
	@make -s -C $(RLINE_PATH) 
	@make -s -C $(PRINTF_PATH)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)/lexer
	mkdir -p $(OBJ_PATH)/builtins
	mkdir -p $(OBJ_PATH)/env
	mkdir -p $(OBJ_PATH)/execution

clean:
	@$(RM) $(OBJS) $(DEPS)
	@$(RM) -rf $(OBJ_PATH)
	@make -s -C $(LIBFT_PATH) clean
	@make -s -C $(PRINTF_PATH) clean

fclean: clean
	@$(RM) $(NAME)
	@make -s -C $(LIBFT_PATH) fclean
	@make -s -C $(PRINTF_PATH) fclean
re: fclean all
# Phony
.PHONY: all clean fclean re
