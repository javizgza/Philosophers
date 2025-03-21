# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/18 10:12:42 by javierzarag       #+#    #+#              #
#    Updated: 2025/03/21 11:05:21 by javierzarag      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -fsanitize=thread -g -Wall -Wextra -Werror -pthread

SRCS = main.c input_utils.c run.c 
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

leaks:
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) 5 800 200 200

leaks_macos:
	leaks --atExit -- ./$(NAME) 5 399 200 200

.PHONY: all clean fclean re

