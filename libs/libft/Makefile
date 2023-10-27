# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 11:52:04 by julolle-          #+#    #+#              #
#    Updated: 2023/10/27 19:19:29 by julolle-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEF_COLOR	:=	\033[1;97m
CIAN		:=	\033[1;96m

NAME		:= libft.a
HEADER      := libft.h

SRCS		:= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
			ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
			ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
			ft_strrchr.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
			ft_strtrim.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
			ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_split.c
SRCSBONUS	:= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS		:= $(SRCS:.c=.o)
OBJSBONUS	:= $(SRCSBONUS:.c=.o)
DEPS		:= $(OBJS:.o=.d)
DEPSBONUS	:= $(OBJSBONUS:.o=.d)

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -MMD
ARFLAGS		:= ar -rcs

RM			:= rm -f
DIR_DUP 	= mkdir -p $(@D)

all: $(NAME)

bonus : $(OBJS) $(OBJSBONUS)
	$(ARFLAGS) $(NAME) $(OBJS) $(OBJSBONUS)
	@touch $@

clean:
	$(RM) $(OBJS) $(OBJSBONUS) $(DEPS) $(DEPSBONUS)
	$(RM) bonus

fclean: clean
	$(RM) $(NAME)

re:	fclean all

$(NAME): $(OBJS)
	$(ARFLAGS) $(NAME) $(OBJS)
	@echo "$(CIAN)LIBFT compiled$(DEF_COLOR)"

%.o: %.c Makefile $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)
-include $(DEPSBONUS)

.PHONY: all clean fclean re
