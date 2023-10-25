# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/03 17:22:44 by julolle-          #+#    #+#              #
#    Updated: 2023/10/25 13:38:39 by julolle-         ###   ########.fr        #
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
			lexer/process_list_utils.c lexer/print_free_list.c \
			lexer/error_parsing.c lexer/heredoc.c \
			execution/exec_process.c execution/manage_process.c \
			execution/pipes.c execution/utils_exec.c execution/parse_path.c \
			builtins/ft_cd.c builtins/ft_echo.c builtins/ft_export.c \
			builtins/ft_pwd.c builtins/ft_unset.c builtins/ft_exit.c \
			env/env_setup.c env/env_modify.c env/env_search.c  env/exp_env.c \
			env/exp_env_2.c
SRCS		= $(addprefix $(SRC_PATH), $(SRC))

LIBFT_PATH	= libs/libft/
LIBFT		= $(LIBFT_PATH)/libft.a

PRINTF_PATH	= libs/ft_printf/
PRINTF		= $(PRINTF_PATH)/libftprintf.a

RLINE_PATH	= libs/readline/
RLINE_MK	= $(RLINE_PATH)/libreadline.a
RLINE		= $(RLINE_PATH)/libreadline.a $(RLINE_PATH)/libhistory.a

LIB_FLAGS	=  $(LIBFT) -L$(LIBFT_PATH) $(PRINTF) -L$(PRINTF_PATH) \
				-lreadline -ltermcap -L$(RLINE_PATH) 

OBJ_PATH	= ./OBJ/
OBJ			= $(addprefix $(OBJ_PATH), $(SRC:.c=.o))
DEP			= $(addprefix $(OBJ_PATH), $(OBJ:.o=.d))

INC_PATH	= ./includes/ ./libs/ $(LIBFT_PATH) $(PRINTF_PATH) $(RLINE_PATH)
INC			= $(addprefix -I, $(INC_PATH))

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -MMD 
RM			= rm -f


all: $(RLINE_MK) $(OBJ_PATH) subsystems $(NAME)
	
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

$(NAME):  $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(LIB_FLAGS)
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

$(RLINE_MK):
	@cd libs/readline && ./configure &>/dev/null
	@$(MAKE) -C $(RLINE_PATH) --no-print-directory
	@echo "$(CIAN)READLINE compiled$(DEF_COLOR)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c Makefile $(LIBFT) $(PRINTF) $(HEADER)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

-include $(DEP)

# Phony
.PHONY: all clean fclean re cleanrl
