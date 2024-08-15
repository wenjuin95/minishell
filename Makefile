# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/26 17:31:26 by tkok-kea          #+#    #+#              #
#    Updated: 2024/08/12 14:37:51 by welow            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

# src and objs
SRC_DIR		:=	scanner parser execution expansion builtin utils
SRC_DIR		:=	${addprefix srcs/, ${SRC_DIR}}
SRC_DIR		+=	srcs
vpath %.c	${SRC_DIR}

SCANNER		=	scanner.c scanner_utils.c
PARSER		=	parser.c parser_utils.c node_contructors.c tree_utils.c
BUILTIN		=	builtin.c echo.c env.c env_utils.c export.c pwd.c\
				unset.c cd.c exit.c export_utils.c
EXPAND		=	expansion.c expansion_steps.c expansion_handler.c \
				expan_utils.c parameter_expand.c \
				ft_str_replace.c
EXECUTE		=	execution.c execution_utils.c execution_utils2.c ft_execvpe.c
SRCS		=	minishell.c \
				signal.c gc_utils.c clean_utils.c env_utils2.c \
				fd_utils.c set_shlvl.c
SRCS		+=	${SCANNER} ${PARSER} ${BUILTIN} ${EXECUTE} ${EXPAND}

OBJ_DIR		=	objs
OBJS		=	${addprefix ${OBJ_DIR}/, ${SRCS:.c=.o}}

# libft
LFT_DIR	=	./libft_42
LIBFT	=	${LFT_DIR}/libft.a

# readline directory needs to be beside the minishell directory (not inside) to complile \
Refer to readme for instructions
RDL_DIR	=	../readline-8.2
RDL_LIB	=	-L${RDL_DIR}/lib -lreadline -lhistory
RDL_INC	=	${RDL_DIR}/include

# compilation and deletion
INCS	=	-Iinclude -I${LFT_DIR} -I${RDL_INC}
CC		= 	gcc
FSAN	=	-fsanitize=address
CFLG	=	-Wall -Wextra -Werror -g3 ${INCS}
RM		=	rm -rf

# Fancy
GREEN = \033[0;32m
RED = \033[0;31m
BOLD = \033[1m
RESET = \033[0m

all:		${NAME}

bonus:		all

${NAME}: ${OBJS} | ${LIBFT}
			@${CC} ${CFLG} ${OBJS} ${LIBFT} ${RDL_LIB} -lncurses -o ${NAME}
			@printf "${GREEN}${BOLD}** Compiled %s **\n${RESET}" $@

${OBJ_DIR}/%.o: %.c | ${OBJ_DIR}
			@printf "\r\033[KCompiling %s\t" $@
			@${CC} ${CFLG} -c $< -o $@
			@printf "\r\033[K"

${OBJ_DIR}:
			@echo "Making obj directory"
			@mkdir $@
			@echo "Compiling objs"

${LIBFT}:
			@echo "Compiling libft"
			@${MAKE} -C ${LFT_DIR}

clean:
			@echo "${RED}Removing obj directory${RESET}"
			@${RM} ${OBJ_DIR}

fclean: clean
			@${MAKE} -C ${LFT_DIR} fclean
			@${RM} ${NAME}
			@echo "${RED}Removed executable ${NAME}${RESET}"

re: fclean all

norm:
			@./norm.sh

.phony: all bonus clean fclean re objects norm
