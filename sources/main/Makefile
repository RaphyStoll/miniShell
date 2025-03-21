# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/20 14:12:04 by Charlye           #+#    #+#              #
#    Updated: 2025/03/21 17:25:46 by Charlye          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------------------------------------------------------------------------
# Configuration de base
# ------------------------------------------------------------------------------
CC         = gcc
CFLAGS     = -Wall -Wextra -Werror
RM         = rm -f

# Nom de l'exécutable principal
NAME       = minishell

# Répertoires des sources
LEXING_DIR  = ./lexing
PARSING_DIR = ./parsing
SIGNALS_DIR = ./signals
LIBFT_DIR   = $(abspath ../../lib/libft)

# Récupération automatique des fichiers sources dans lexing/ et parsing/
LEXING_SRCS  = $(wildcard $(LEXING_DIR)/*.c)
PARSING_SRCS = $(wildcard $(PARSING_DIR)/*.c)
SIGNALS_SRCS = $(wildcard $(SIGNALS_DIR)/*.c)
MAIN_SRC     = main.c

# Tous les fichiers sources
SRCS       = $(LEXING_SRCS) $(PARSING_SRCS) $(SIGNALS_SRCS) $(MAIN_SRC)
OBJS       = $(SRCS:.c=.o)

# Librairies et includes
LIBFT_A    = $(LIBFT_DIR)/output/libft.a
INCLUDES   = -I$(LIBFT_DIR)/header -I/opt/homebrew/opt/readline/include -I$(LEXING_DIR) -I$(PARSING_DIR) -I$(SIGNALS_DIR)

# ------------------------------------------------------------------------------
# Compilation principale
# ------------------------------------------------------------------------------
all: $(LIBFT_A) $(NAME)

# Compilation de l'exécutable
$(NAME): $(OBJS)
	@echo "🔗 Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR)/output -lft -L/opt/homebrew/opt/readline/lib -lreadline -o $(NAME)
	@echo "✅ Build successful!"

# Compilation des fichiers objets
%.o: %.c
	@echo "🛠️  Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

# ------------------------------------------------------------------------------
# Compilation de libft si nécessaire
# ------------------------------------------------------------------------------
$(LIBFT_A):
	@echo "📦 Building libft..."
	@$(MAKE) -C $(LIBFT_DIR) all

# ------------------------------------------------------------------------------
# Nettoyage
# ------------------------------------------------------------------------------
clean:
	@echo "🧹 Cleaning object files..."
	$(RM) $(OBJS)

fclean: clean
	@echo "🧹 Removing executable..."
	$(RM) $(NAME)

re: fclean all

# ------------------------------------------------------------------------------
# Règles phony
# ------------------------------------------------------------------------------
.PHONY: all clean fclean re