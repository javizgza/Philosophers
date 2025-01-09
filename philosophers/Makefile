# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jazarago <jazarago@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/18 10:12:42 by javierzarag       #+#    #+#              #
#    Updated: 2025/01/09 11:57:33 by jazarago         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c input_utils.c run.c 
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) 4 410 200 200

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

