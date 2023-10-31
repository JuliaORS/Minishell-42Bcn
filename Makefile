# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/03 17:22:44 by julolle-          #+#    #+#              #
#    Updated: 2023/10/31 11:02:11 by julolle-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEF_COLOR	:=	\033[1;97m
PINK		:=	\033[1;95m
GREEN		:=	\033[1;92m
CIAN		:=	\033[1;96m

NAME        = minishell

HEADER      = ./includes/minishell.h ./includes/defines.h

SRC_PATH    = srcs/
SRC         = minishell.c signals.c lexer/manage_input.c lexer/parser.c \
			lexer/token_list.c lexer/token_list_utils.c lexer/expander.c \
			lexer/expander_utils.c lexer/expander_utils2.c \
			lexer/process_list.c lexer/process_list_files.c \
			lexer/process_list_utils.c lexer/free_lexer.c \
			lexer/debug_lexer.c lexer/error_parsing.c execution/heredoc.c \
			execution/exec_process.c execution/manage_process.c \
			execution/pipes.c execution/utils_exec.c execution/utils_exec_2.c \
			execution/parse_path.c  builtins/ft_cd.c builtins/ft_echo.c \
			builtins/ft_export.c builtins/ft_pwd.c builtins/ft_unset.c \
			builtins/ft_exit.c builtins/bltn_utils.c env/env_setup.c \
			env/env_modify.c env/env_search.c env/exp_env.c env/exp_env_2.c
SRCS		= $(addprefix $(SRC_PATH), $(SRC))

LIBFT_PATH	= libs/libft/
LIBFT		= $(LIBFT_PATH)/libft.a

PRINTF_PATH	= libs/ft_printf/
PRINTF		= $(PRINTF_PATH)/libftprintf.a

RLINE_PATH	= libs/readline/
RLINE		= $(RLINE_PATH)/libreadline.a
RLINE_H		= $(RLINE_PATH)/libhistory.a

LIB_PATH	= -L$(LIBFT_PATH) -L$(PRINTF_PATH) -L$(RLINE_PATH) 
LIB_FLAGS	= $(LIBFT) $(PRINTF) -lreadline -ltermcap 

OBJ_PATH	= ./OBJ/
OBJ			= $(addprefix $(OBJ_PATH), $(SRC:.c=.o))
DEP			= $(addprefix $(OBJ_PATH), $(OBJ:.o=.d))

INC_PATH	= ./includes/ ./libs/ $(LIBFT_PATH) $(PRINTF_PATH) $(RLINE_PATH)
INC			= $(addprefix -I, $(INC_PATH))

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -MMD 
RM			= rm -f


all: $(RLINE) $(OBJ_PATH) subsystems $(NAME)
	
clean:
	@$(RM) $(OBJS) $(DEPS)
	@$(RM) -rf $(OBJ_PATH)
	@make -s -C $(LIBFT_PATH) clean
	@make -s -C $(PRINTF_PATH) clean
	@echo "$(PINK)Objects removed$(DEF_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@make -s -C $(LIBFT_PATH) fclean
	@make -s -C $(PRINTF_PATH) fclean
	@echo "$(PINK)Minishell removed$(DEF_COLOR)"

re: fclean all

cleanrl:
	@make -s -C $(RLINE_PATH) mostlyclean
	@echo "$(PINK)READLINE removed$(DEF_COLOR)"

$(NAME)::  $(OBJ) ./$(LIBFT) ./$(PRINTF) ./$(RLINE) ./$(RLINE_H)
	@$(CC) $(CFLAGS) $(^) -ltermcap -lreadline -o $(NAME)
	@echo "$(GREEN)MINISHELL compiled :D$(DEF_COLOR)"

subsystems:
	@make -s -C $(LIBFT_PATH)
	@make -s -C $(PRINTF_PATH)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)/lexer
	@mkdir -p $(OBJ_PATH)/builtins
	@mkdir -p $(OBJ_PATH)/env
	@mkdir -p $(OBJ_PATH)/execution

$(RLINE):
	@cd libs/readline && ./configure &>/dev/null
	@$(MAKE) -C $(RLINE_PATH) --no-print-directory
	@echo "$(CIAN)READLINE compiled$(DEF_COLOR)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c Makefile $(HEADER)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

-include ${DEP}

# Phony
.PHONY: all clean fclean re cleanrl
