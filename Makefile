# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/17 18:27:27 by ofadhel           #+#    #+#              #
#    Updated: 2023/11/21 15:54:37 by ofadhel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= minishell

SRCS 	= main.c lexertest.c executortest.c

#libft

LIBFT_PATH 	= ./libft

LIBFT 	= $(LIBFT_PATH)


CC 		= gcc

CFLAGS 	= -Wall -Wextra -Werror -lreadline

OBJS 	= $(SRCS:.c=.o)

%.o: %.c
			$(CC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
		@echo "$(COLOUR_YELLOW)COMPILING...$(COLOUR_END)"
		make -C $(LIBFT_PATH)
		$(CC) $(OBJS) $(LIBFT)/libft.a -o $(NAME) $(CFLAGS)
		@echo "$(COLOUR_GREEN)READY TO GO!$(COLOUR_END)"

clean:
		rm -f $(OBJS)
		make fclean -C ${LIBFT_PATH}

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
