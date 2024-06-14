# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/26 17:31:26 by tkok-kea          #+#    #+#              #
#    Updated: 2024/06/13 16:43:55 by tkok-kea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	rdp_calc.out

# src and objs
SRC		=	main.c lexer_utils.c parser_utils.c parser_rules.c
SRC		+=	parse_ast.c
OBJS	=	${SRC:.c=.o}

# libft
LFT_DIR	=	../libft_42
LIBFT	=	${LFT_DIR}/libft.a

# readline (changes depending on machine)
UNAME	= $(shell uname -s)
ifeq ($(UNAME), Linux)
RDL_DIR	=	../rdl
RDL_LIB	=	-lreadline -lhistory
endif
ifeq ($(UNAME), Darwin)
RDL_DIR	=	../rdl
RDL_LIB	=	-L${RDL_DIR}/lib -lreadline -lhistory
endif
RDL_INC	=	${RDL_DIR}/include

# compilation
INCS	=	-Iinclude -I${LFT_DIR} -I${RDL_INC} 
CC		= 	gcc
CFLG	=	-Wall -Wextra -Werror ${INCS}

${RM}	=	rm -rf

all:		${NAME}

bonus:		all

${NAME}:	${LIBFT} ${OBJS}
			${CC} ${CFLG} ${OBJS} ${LIBFT} ${RDL_LIB} -lncurses -lm -o ${NAME}

%.o:		%.c
			${CC} ${CFLG} -c $< -o $@

${LIBFT}:
			${MAKE} -C ${LFT_DIR}

clean:		
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.phony:		all bonus clean fclean re clean_rl