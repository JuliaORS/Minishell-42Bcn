# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/03 17:22:44 by julolle-          #+#    #+#              #
#    Updated: 2023/10/24 12:41:34 by julolle-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell

HEADER      = ./includes/minishell.h

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
			env/env_setup.c env/env_modify.c env/env_search.c
SRCS		= $(addprefix $(SRC_PATH), $(SRC))

LIBFT_PATH	= libs/libft/
LIBFT		= $(LIBFT_PATH)/libft.a

PRINTF_PATH	= libs/ft_printf/
PRINTF		= $(PRINTF_PATH)/libftprintf.a

RLINE_PATH	= libs/readline/
RLINE_MK	= $(RLINE_PATH)/Makefile
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

fclean: clean
	@$(RM) $(NAME)
	@make -s -C $(LIBFT_PATH) fclean
	@make -s -C $(PRINTF_PATH) fclean

re: fclean all

readline:
	@make $(RLINE_MK)

cleanrl:
	@make clean -s -C $(RLINE_PATH)


$(NAME):  $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(LIB_FLAGS)
	$(info MINISHELL compiled)

subsystems:
	@make -s -C $(LIBFT_PATH)
	@make -s -C $(PRINTF_PATH)
	@make -s -C $(RLINE_PATH) 

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)/lexer
	mkdir -p $(OBJ_PATH)/builtins
	mkdir -p $(OBJ_PATH)/env
	mkdir -p $(OBJ_PATH)/execution

$(RLINE_MK):
	pwd ${BLOCK}
	cd ./${RLINE_PATH} && ./configure
	cd ${BLOCK}

$(OBJ_PATH)%.o: $(SRC_PATH)%.c Makefile $(LIBFT) $(RLINE) $(PRINTF) $(HEADER)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

-include $(DEP)

# Phony
.PHONY: all clean fclean re readline cleanrl
