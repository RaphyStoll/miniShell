# ------------------------------------------------------------------------------
# Configuration de base
# ------------------------------------------------------------------------------
CC         = gcc
CFLAGS     = -Wall -Wextra -Werror
RM         = rm -f

# Nom de l'exécutable
NAME       = test_env

# Fichiers sources (tous les fichiers .c du dossier actuel)
SRCS       = $(wildcard *.c)
OBJS       = $(SRCS:.c=.o)

# Répertoire de la libft (on remonte 3 fois dans l'arborescence)
LIBFT_DIR  = $(abspath ../../../lib/libft)
LIBFT_A    = $(LIBFT_DIR)/output/libft.a

# Options d'inclusion
INCLUDES = -I $(LIBFT_DIR)/header -I ../../../includes/main -I/usr/local/opt/readline/include

# ------------------------------------------------------------------------------
# Compilation principale
# ------------------------------------------------------------------------------
all: $(LIBFT_A) $(NAME)

# Compilation de l'exécutable
$(NAME): $(OBJS)
	@echo "🔗 Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR)/output -lft -L/usr/local/opt/readline/lib -lreadline -o $(NAME)
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
	@$(MAKE) -C $(LIBFT_DIR)

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
