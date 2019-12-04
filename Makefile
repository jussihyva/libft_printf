# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@hive.fi>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/04 11:34:07 by jkauppi           #+#    #+#              #
#    Updated: 2019/12/04 13:49:29 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libftprintf.a
SRC_FOLDER		=	./src

LIBFT_FOLDER	=	./libft
LIBFT_NAME		=	ft
OBJ_FOLDER		=	./obj
CC				=	clang

INCLUDES		=	-I ${SRC_FOLDER} -I ${LIBFT_FOLDER}
CFLAGS			=	-Wall -Werror -Wextra -g ${INCLUDES}

SRC_FILES		=	ft_printf.c
HEADER_FILE		=	ft_printf.h
SRC_PATHS		=	${addprefix ${SRC_FOLDER}/, ${SRC_FILES}}
OBJ_PATHS		=	${addprefix ${OBJ_FOLDER}/, ${patsubst %.c,%.o,${SRC_FILES}}}
LIBFT_FILES		=	ft_putstr.o
LIBFT_PATHS		=	${addprefix ${LIBFT_FOLDER}/, ${LIBFT_FILES}}

all: ${NAME}

${NAME}:  ${OBJ_PATHS}
	ar -rcs ${NAME} ${OBJ_PATHS} ${LIBFT_PATHS}

${OBJ_PATHS}:${OBJ_FOLDER}/%.o: ${SRC_FOLDER}/%.c ${SRC_FOLDER}/${HEADER_FILE}
	make -C ${LIBFT_FOLDER}
	${CC} ${CFLAGS} -c -o $@ $<

clean:
	\rm ${OBJ_PATHS}

fclean: clean
	\rm ${NAME}

re: fclean all

.PHONY: re fclean clean all

