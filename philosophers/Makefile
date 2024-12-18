# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/18 10:12:42 by javierzarag       #+#    #+#              #
#    Updated: 2024/12/18 11:11:35 by javierzarag      ###   ########.fr        #
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

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

