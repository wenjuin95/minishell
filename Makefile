NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC = main.c history.c signal.c environment.c 

OBJ_FOLDER = object_files

OBJ_SRC = $(addprefix $(OBJ_FOLDER)/, $(SRC:.c=.o))

all : $(NAME)

$(NAME) : $(OBJ_SRC)
	@make -C libft
	@cp libft/libft.a .
	$(CC) $(CFLAGS) $(OBJ_SRC) libft.a -o $@ -lreadline

$(OBJ_FOLDER)/%.o : %.c | $(OBJ_FOLDER)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_FOLDER):
	@mkdir -p $(OBJ_FOLDER)

clean :
	rm -rf $(OBJ_FOLDER)
	@make -C libft clean
	rm -f libft.a

fclean : clean
	rm -f $(NAME)
	@make -C libft fclean

re : fclean all

.PHONY: all clean fclean re
