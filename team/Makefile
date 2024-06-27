# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/26 17:31:26 by tkok-kea          #+#    #+#              #
#    Updated: 2024/06/27 15:11:11 by welow            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

# src and objs
SRC_DIR		:=	scanner parser builtin execution
SRC_DIR		:=	${addprefix srcs/, ${SRC_DIR}}
SRC_DIR		+=	srcs
vpath %.c	${SRC_DIR}

SCANNER		=	scanner.c scanner_utils.c
PARSER		=	parser.c parser_utils.c
BUILTIN		=	builtin.c echo.c env.c env_utils.c export.c pwd.c\
				unset.c cd.c exit.c
EXECUTE		=	execution.c ft_execvp.c
SRCS		=	minishell.c signal.c utils.c
SRCS		+=	${SCANNER} ${PARSER} ${BUILTIN} ${EXECUTE}
OBJ_DIR		=	objs
OBJS	=	${addprefix ${OBJ_DIR}/, ${SRCS:.c=.o}}


# libft
LFT_DIR	=	./libft_42
LIBFT	=	${LFT_DIR}/libft.a

# readline (changes depending on machine)
UNAME	= $(shell uname -s)
ifeq ($(UNAME), Linux)
RDL_DIR	=	./rdl
RDL_LIB	=	-lreadline -lhistory
endif
ifeq ($(UNAME), Darwin)
RDL_DIR	=	./rdl
RDL_LIB	=	-L${RDL_DIR}/lib -lreadline -lhistory
endif
RDL_INC	=	${RDL_DIR}/include

# compilation
INCS	=	-Iinclude -I${LFT_DIR} -I${RDL_INC}
CC		= 	gcc
FSAN	=	-fsanitize=address
CFLG	=	-Wall -Wextra -Werror ${FSAN} -g ${INCS}

RM		=	rm -rf


all:		${NAME}

bonus:		all

${NAME}:	${OBJS} | ${LIBFT}
			${CC} ${CFLG} ${OBJS} ${LIBFT} ${RDL_LIB} -lncurses -o ${NAME}

${OBJ_DIR}/%.o:		%.c | ${OBJ_DIR}
			${CC} ${CFLG} -c $< -o $@

${OBJ_DIR}:
			@echo "making obj directory"
			@mkdir $@

${LIBFT}:
			${MAKE} -C ${LFT_DIR}

clean:		
			@echo "Removing obj directory"
			@${RM} ${OBJ_DIR}

fclean:		clean
			${MAKE} -C ${LFT_DIR} fclean
			@${RM} ${NAME}
			@echo "Removed executable ${NAME}"

re:			fclean all

.phony:		all bonus clean fclean re