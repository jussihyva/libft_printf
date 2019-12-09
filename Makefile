# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/04 11:34:07 by jkauppi           #+#    #+#              #
#    Updated: 2019/12/09 13:43:28 by jkauppi          ###   ########.fr        #
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

SRC_FILES		=	ft_printf.c split_input_string.c create_converters.c \
					ft_ltoa_base.c
HEADER_FILE		=	ft_printf.h
SRC_PATHS		=	${addprefix ${SRC_FOLDER}/, ${SRC_FILES}}
OBJ_PATHS		=	${addprefix ${OBJ_FOLDER}/, ${patsubst %.c,%.o,${SRC_FILES}}}
LIBFT_FILES		=	ft_putstr.o ft_putstr_fd.o ft_strlen.o ft_putchar.o \
					ft_putchar_fd.o ft_putnbr.o ft_putnbr_fd.o ft_lstadd_e.o \
					ft_memalloc.o ft_strchr.o ft_strnew.o ft_bzero.o \
					ft_memchr.o ft_memset.o ft_strdel.o ft_memdel.o ft_itoa.o \
					ft_strjoin.o ft_strcpy.o ft_memmove.o ft_toupper.o \
					ft_islower.o
LIBFT_PATHS		=	${addprefix ${LIBFT_FOLDER}/, ${LIBFT_FILES}}

all: ${NAME}

${NAME}:  ${OBJ_PATHS}
	ar -rcs ${NAME} ${OBJ_PATHS} ${LIBFT_PATHS}

${OBJ_PATHS}:${OBJ_FOLDER}/%.o: ${SRC_FOLDER}/%.c ${SRC_FOLDER}/${HEADER_FILE}
	make -C ${LIBFT_FOLDER}
	${CC} ${CFLAGS} -c -o $@ $<

clean:
	\rm -f ${OBJ_PATHS}

fclean: clean
	\rm -f ${NAME}

re: fclean all

.PHONY: re fclean clean all

