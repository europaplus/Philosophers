# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: knfonda <knfonda@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/19 14:30:06 by ngarkbit          #+#    #+#              #
#    Updated: 2021/03/08 16:35:25 by knfonda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo_three

SRCS		= 	./srcs/

SRC_PH		=	$(addprefix $(SRCS), main.c initialization.c utils.c parse.c)

SRC_OBJ		=	$(SRC_PH:.c=.o)

INCL		=	./includes/philosopher.h

CC			=	gcc

RM			=	rm -f

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