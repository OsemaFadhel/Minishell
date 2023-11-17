# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/17 18:27:27 by ofadhel           #+#    #+#              #
#    Updated: 2023/11/17 18:45:39 by ofadhel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= minishell

SRCS 	= main.c

CC 		= gcc

CFLAGS 	= -Wall -Wextra -Werror -lreadline

OBJS 	= $(SRCS:.c=.o)

%.o: %.c
			$(CC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
