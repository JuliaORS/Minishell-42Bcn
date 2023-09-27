CC = CC

FLAGS = -MMD -I/.
SRC =  main_romain.c exec_process.c manage_process.c utils_exec.c pipes.c ../builtins/env_setup.c
OBJS = $(SRC:.c=.o)
DEPS = $(SRC:.c=.d)

LIBFT_PATH = ../includes/libft
LIBFT = $(LIBFT_PATH)/libft.a
NAME = exec_process

all: $(LIBFT) $(NAME)

-include $(DEPS)
$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH) all
%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@
 
clean:
	make -C $(LIBFT_PATH) clean
	rm -rf $(OBJS) $(DEPS)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -rf $(NAME)
	

re: fclean all

.phony: clean re all fclean
