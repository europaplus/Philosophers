# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: knfonda <knfonda@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/19 14:30:06 by ngarkbit          #+#    #+#              #
#    Updated: 2021/03/08 16:38:30 by knfonda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo_two

SRCS		= 	./srcs/

SRC_PH		=	$(addprefix $(SRCS), main.c initialization.c utils.c parse.c)

SRC_OBJ		=	$(SRC_PH:.c=.o)

INCL		=	./includes/philosopher.h

CC			=	gcc

RM			=	rm -f

PG			= 	philo_two

CFLAGS		= 	-Wall -Werror -Wextra

all: $(NAME)

%.o: %.c $(INCL)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(SRC_OBJ) $(INCL)
	$(CC) -o $(NAME) $(SRC_OBJ)


clean:
	$(RM) $(SRC_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all