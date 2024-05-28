NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I/usr/local/opt/readline/include

RL_DIR = minishell/readline

#-L is used to specify the directory where the library is located
#-I is used to specify the directory where the header files are located
RL = -L/Users/welow/Desktop/github/minishell/readline -I$(RL_DIR) -lreadline -lncurses -lhistory 

SRC = main.c signal.c execute.c utils.c builtin/echo.c builtin/pwd.c builtin/env.c buildin/env_utils.c

OBJ_FOLDER = object_files

OBJ_SRC = $(addprefix $(OBJ_FOLDER)/, $(SRC:.c=.o))

all : $(NAME)

$(NAME) : $(OBJ_SRC)
	@make -C libft
	@cp libft/libft.a .
	$(CC) $(CFLAGS) $(OBJ_SRC) libft.a -o $@ $(RL)

$(OBJ_FOLDER)/%.o : %.c | $(OBJ_FOLDER)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_FOLDER):
	@mkdir -p $(dir $(OBJ_SRC))

clean :
	rm -rf $(OBJ_FOLDER)
	@make -C libft clean
	rm -f libft.a

fclean : clean
	rm -f $(NAME)
	@make -C libft fclean

re : fclean all

.PHONY: all clean fclean re
