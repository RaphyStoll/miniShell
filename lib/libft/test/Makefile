
AR = ar rcs
RM = rm -f

FILES =	test_ft_isalpha \
		test_ft_isdigit \
		test_ft_isalnum \
		test_ft_isprint \
		test_ft_isascii \
		test_ft_strlen \
		test_ft_memset \
		test_ft_bzero \
		test_ft_memcpy \
		test_ft_memmove \
		test_ft_strlcpy \
		test_ft_strlcat \
		test_ft_toupper \
		test_ft_tolower \
		test_ft_strchr \
		test_ft_strrchr \
		test_ft_strncmp \
		test_ft_memchr \
		test_ft_memcmp \
		test_ft_strnstr \
		test_ft_atoi \
		test_ft_calloc \
		test_ft_strdup \
		test_ft_substr \
		test_ft_strjoin \
		test_ft_strtrim \
		test_ft_split \
		test_ft_itoa \
		test_ft_strmapi \
		test_ft_striteri \
		test_ft_putchar_fd \
		test_ft_putstr_fd \
		test_ft_putendl_fd \
		test_ft_putnbr_fd \
		test_ft_lstnew \
		test_ft_lstadd_front \
		test_ft_lstsize \
		test_ft_lstlast \
		test_ft_lstadd_back \
		test_ft_lstdelone \
		test_ft_lstclear \
		test_ft_lstiter \
		test_ft_lstmap \

# Répertoire de sortie
OUTPUT_DIR = ../output

# Noms de fichiers de sortie avec extension .out
OUTPUT_FILES = $(addsuffix .out, $(addprefix $(OUTPUT_DIR)/, $(FILES)))

# Drapeaux de compilation
CFLAGS = -Werror -Wextra -Wall -I ../src/libft

# Règle par défaut
all: $(OUTPUT_DIR) $(OUTPUT_FILES)

# Créer le répertoire de sortie si nécessaire
$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

# Règle de compilation des fichiers de test
$(OUTPUT_DIR)/%.out: %.c ../src/libft.a
	gcc $(CFLAGS) $< ../src/libft.a -o $@

# Règle de nettoyage
clean:
	rm -f $(OUTPUT_FILES)

fclean: clean
	rm -rf $(OUTPUT_DIR)

re: fclean all

.PHONY: all clean fclean re