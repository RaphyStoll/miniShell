# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/07 14:04:38 by Charlye           #+#    #+#              #
#    Updated: 2025/04/07 14:04:47 by Charlye          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = signals.c
OBJS = $(SRCS:.c=.o)

READLINE_PATH = /opt/homebrew/opt/readline
CFLAGS = -Wall -Wextra -Werror -I$(READLINE_PATH)/include
LDFLAGS = -L$(READLINE_PATH)/lib -lreadline

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)