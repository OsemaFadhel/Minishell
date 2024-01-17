# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/17 18:27:27 by ofadhel           #+#    #+#              #
#    Updated: 2024/01/17 19:37:08 by ofadhel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= minishell

SRCS 	= 	main.c utils1.c signals.c error.c \
			lexer/lexer.c lexer/count_words.c lexer/add_str.c \
			lexer/lex_env.c lexer/checks.c \
			parser/parser.c parser/init_pars.c \
			parser/parser_counts.c parser/parser_red.c \
			executor/executortest.c executor/builtin.c \
			executor/executor_fds.c executor/executor.c \
			executor/executor_fds2.c executor/builtin2.c \
			executor/builtin_exit.c executor/builtin_unset.c \
			executor/builtin_cd.c executor/builtin_export.c \
			executor/builtin_export2.c executor/builtin_export3.c \
			free.c \

#libft

LIBFT_PATH 	= ./libft

LIBFT 	= $(LIBFT_PATH)


CC 		= gcc

READLINE 	= -L/usr/include -lreadline

CFLAGS 	= -Wall -Wextra -Werror

OBJS 	= $(SRCS:.c=.o)

%.o: %.c
			$(CC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
		@echo "$(COLOUR_YELLOW)COMPILING...$(COLOUR_END)"
		make -C $(LIBFT_PATH)
		$(CC) $(OBJS) $(LIBFT)/libft.a -o $(NAME) $(CFLAGS) $(READLINE)
		@echo "$(COLOUR_GREEN)READY TO GO!$(COLOUR_END)"

clean:
		rm -f $(OBJS)
		make fclean -C ${LIBFT_PATH}

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
