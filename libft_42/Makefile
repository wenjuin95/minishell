# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkok-kea <tkok-kea@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/04 20:26:50 by tkok-kea          #+#    #+#              #
#    Updated: 2024/06/26 14:35:03 by tkok-kea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
		  ft_isspace.c \
		  ft_strlen.c  ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c\
		  ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c\
		  ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c\
		  ft_strnstr.c ft_atoi.c ft_atoi_base.c ft_calloc.c ft_strdup.c\
		  ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c\
		  ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c\
		  ft_putendl_fd.c ft_putnbr_fd.c get_next_line.c ft_strcmp.c\
		  ft_min.c ft_mult_strjoin.c\

OBJS	= $(SRC:.c=.o)

BONUS	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
		  ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c\
		  ft_lstiter.c ft_lstmap.c ft_lstdel_back.c\

BOBJS		= $(BONUS:.c=.o)

PRINTF_DIR 	= ./ft_printf/

PRINTF_SRC	= ft_printf.c ft_printf_cs.c ft_print_ptr.c ft_print_dec.c \
			ft_print_hex.c ft_printf_utils.c ft_printf_utils2.c ft_set_flags.c\

PRINTF_SRCS	= ${addprefix ${PRINTF_DIR}, ${PRINTF_SRC}}

PRINTF_OBJS	= $(PRINTF_SRCS:.c=.o)

NAME	= libft.a

AR		= ar rcs

RM 		= rm -f

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all:	$(NAME)

$(NAME):	$(OBJS) $(BOBJS) $(PRINTF_OBJS)
		@$(AR) $(NAME) $(OBJS) $(BOBJS) $(PRINTF_OBJS)
		@echo "${GREEN}Compiled library: $@ ${RESET}"

%.o:	%.c
		@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
		@$(RM) $(OBJS) $(BOBJS) $(PRINTF_OBJS)

fclean:	clean
		@echo "${RED}Removing ${NAME}${RESET}"
		@$(RM) $(NAME)

re:		fclean all

.PHONY:	all clean fclean re
