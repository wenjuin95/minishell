NAME = minishell

CC = gcc

INC = -Iinclude -I$(LIBFT_DIR) -I$(RL_INC)

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g $(INC)

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

RL_INC = /Users/welow/Desktop/github/minishell/re_minishell/readline/include

RL_DIR = /Users/welow/Desktop/github/minishell/re_minishell/readline/lib

#-L is used to specify the directory where the library is located
#-I is used to specify the directory where the header files are located
RL = -L$(RL_DIR) -lreadline -lhistory 

#remove builtin/cd.c
SRC = main.c signal.c execute.c utils.c builtin/echo.c builtin/pwd.c builtin/env.c \
	 builtin/unset.c builtin/exit.c builtin/export.c builtin/env_utils.c builtin/cd.c\

OBJ_FOLDER = object_files

OBJ_SRC = $(addprefix $(OBJ_FOLDER)/, $(SRC:.c=.o))

all : $(NAME)

$(NAME) : $(OBJ_SRC)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ_SRC) $(LIBFT) $(RL) -lncurses -o $@ 

$(OBJ_FOLDER)/%.o : %.c | $(OBJ_FOLDER)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_FOLDER):
	@mkdir -p $(dir $(OBJ_SRC))

clean :
	rm -rf $(OBJ_FOLDER)
	@make -C $(LIBFT_DIR) clean

fclean : clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re : fclean all

.PHONY: all clean fclean re
