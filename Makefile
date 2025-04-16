# ------------------------------------------------------------------------------
# Configuration principale
# ------------------------------------------------------------------------------

USE_GNL     = no
USE_PRINTF  = no
USE_LIBFT   = yes
USE_BONUS   = no
USE_ANIM	= yes

NAME        = output/minishell
NAME_BONUS  = output/minishell_bonus

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    READLINE_DIR = /opt/homebrew/opt/readline
    CFLAGS  += -I$(READLINE_DIR)/include
    LDFLAGS += -L$(READLINE_DIR)/lib -lreadline
else
    LDFLAGS += -lreadline
endif

INCLUDES        = -I includes/main/ -I includes/bonus/
INCLUDES_BONUS  = -I includes/bonus/

MKDIR   = mkdir -p
RM      = rm -f

# Couleurs
BLACK   = \033[0;30m
RED     = \033[0;91m
GREEN   = \033[0;92m
YELLOW  = \033[0;93m
BLUE    = \033[0;94m
MAGENTA = \033[0;95m
CYAN    = \033[0;96m
WHITE   = \033[0;97m
BOLD    = \033[1m
RESET   = \033[0m

SRC_DIR     = sources
OBJ_DIR     = objects
MAIN_DIR    = $(SRC_DIR)/main
BONUS_DIR   = $(SRC_DIR)/bonus
OUTPUT_DIR  = output

LIB_DIR       = lib
FT_PRINTF_DIR = ft_printf
GNL_DIR       = gnl
LIBFT_DIR     = libft

FT_PRINTF_LIB = $(LIB_DIR)/$(FT_PRINTF_DIR)/libftprintf.a
GNL_LIB       = $(LIB_DIR)/$(GNL_DIR)/libgnl.a
LIBFT_LIB     = $(LIB_DIR)/$(LIBFT_DIR)/output/libft.a

ALL_LIBS =

ifeq ($(USE_PRINTF), yes)
    ALL_LIBS += $(FT_PRINTF_LIB)
endif
ifeq ($(USE_GNL), yes)
    ALL_LIBS += $(GNL_LIB)
endif
ifeq ($(USE_LIBFT), yes)
    ALL_LIBS += $(LIBFT_LIB)
endif

SRC_FILES := $(shell find $(MAIN_DIR) -name '*.c' ! -name 'test_*.c')
OBJ_FILES := $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRC_FILES:.c=.o))

BONUS_SRC_FILES := $(shell find $(BONUS_DIR) -name '*.c' ! -name 'test_*.c')
BONUS_OBJ_FILES := $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(BONUS_SRC_FILES:.c=.o))

ifeq ($(USE_BONUS), yes)
    ALL_OBJS := $(OBJ_FILES) $(BONUS_OBJ_FILES)
else
    ALL_OBJS := $(OBJ_FILES)
endif

DIRS_TO_CREATE := $(sort $(dir $(ALL_OBJS)))

# ------------------------------------------------------------------------------
# Cibles principales
# ------------------------------------------------------------------------------
all: dirs $(ALL_LIBS) $(NAME)

dirs:
	@$(MKDIR) $(OUTPUT_DIR) $(DIRS_TO_CREATE)

ifeq ($(USE_BONUS), yes)
bonus: $(ALL_LIBS) $(NAME_BONUS)
endif

# ------------------------------------------------------------------------------
# Compilation binaire principal
# ------------------------------------------------------------------------------
$(NAME): $(ALL_OBJS) | $(OUTPUT_DIR)
	@set -e; \
	# — Choix d’une couleur ANSI aléatoire entre 30 et 97 —; \
	colors="30 31 32 33 34 35 36 37 90 91 92 93 94 95 96 97"; \
	color=$$(echo $$colors | tr ' ' '\n' | shuf -n1); \
	# — Linking —; \
	printf "\033[2K\r$(CYAN)→ Linking objects...$(RESET)"; \
	$(CC) $(CFLAGS) $(ALL_OBJS) $(ALL_LIBS) -o $(NAME) $(LDFLAGS); \
	printf "\033[2K\r$(BOLD)$(GREEN)✔ Finished building $(NAME)$(RESET)\n"; \
	# — Nettoyage de l’écran et ASCII art en couleur aléatoire —; \
	clear; \
	printf "\033[1;$$color""m%b$(RESET)\n" "\
███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n\
████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n\
██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n\
██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n\
██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n\
╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"; \
	# — Message de succès —; \
	printf "\033[0;92m✨ Minishell built successfully!$(RESET)\n"; \
	# — Résumé —; \
	count=$$(find $(OBJ_DIR) -name '*.o' | wc -l); \
	libcount=$$(echo "$(ALL_LIBS)" | wc -w); \
	build_date=$$(date +"%Y-%m-%d %H:%M:%S"); \
	printf "\n$(BOLD)📦 Build summary:$(RESET)\n"; \
	printf "  $(WHITE)• 🧱 Files compiled   :$(RESET) $(GREEN)$$count$(RESET)\n"; \
	printf "  $(WHITE)• 📚 Libraries linked:$(RESET) $(GREEN)$$libcount$(RESET)\n"; \
	printf "  $(WHITE)• 📂 Exec path       :$(RESET) $(CYAN)$(NAME)$(RESET)\n"; \
	printf "  $(WHITE)• 🕒 Date           :$(RESET) $(CYAN)$$build_date$(RESET)\n"


# ------------------------------------------------------------------------------
# Compilation binaire bonus
# ------------------------------------------------------------------------------
$(NAME_BONUS): $(BONUS_OBJ_FILES) | $(OUTPUT_DIR)
	@printf "\033[2K\r$(CYAN)→ Linking bonus...$(RESET)"
	@$(CC) $(CFLAGS) $(BONUS_OBJ_FILES) $(ALL_LIBS) -o $(NAME_BONUS) $(LDFLAGS)
	@printf "\033[2K\r$(BOLD)$(GREEN)✔ Finished building $(NAME_BONUS)$(RESET)\n"

# ------------------------------------------------------------------------------
# Compilation générique (main + bonus)
# ------------------------------------------------------------------------------
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@printf "\033[2K\r$(BLUE)Compiling $< → $@$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@printf "\033[2K\r$(GREEN)✔ Compiled $<$(RESET)\n"

# ------------------------------------------------------------------------------
# Compilation des bibliothèques
# ------------------------------------------------------------------------------
define build_lib
$(1):
	@printf "\033[2K\r$(YELLOW)→ Building $(2) library...$(RESET)"
	@$(MAKE) --no-print-directory -C $(LIB_DIR)/$(3)
endef

ifeq ($(USE_PRINTF), yes)
    $(eval $(call build_lib,$(FT_PRINTF_LIB),PRINTF,$(FT_PRINTF_DIR)))
endif
ifeq ($(USE_GNL), yes)
    $(eval $(call build_lib,$(GNL_LIB),GNL,$(GNL_DIR)))
endif
ifeq ($(USE_LIBFT), yes)
    $(eval $(call build_lib,$(LIBFT_LIB),LIBFT,$(LIBFT_DIR)))
endif

# ------------------------------------------------------------------------------
# Nettoyage
# ------------------------------------------------------------------------------
clean:
	@printf "\033[2K\r$(RED)→ Removing object files...$(RESET)"
	@$(RM) -r $(OBJ_DIR)
	@printf "\033[2K\r$(GREEN)✔ Cleaned object files$(RESET)\n"

fclean: clean
	@printf "\033[2K\r$(RED)→ Removing executables...$(RESET)"
	@$(RM) $(NAME) $(NAME_BONUS)
	@printf "\033[2K\r$(GREEN)✔ Removed executables$(RESET)\n"
ifeq ($(USE_PRINTF), yes)
	@printf "\033[2K\r$(RED)→ Cleaning Printf...$(RESET)"
	@$(MAKE) --no-print-directory -C $(LIB_DIR)/$(FT_PRINTF_DIR) fclean
endif
ifeq ($(USE_GNL), yes)
	@printf "\033[2K\r$(RED)→ Cleaning GNL...$(RESET)"
	@$(MAKE) --no-print-directory -C $(LIB_DIR)/$(GNL_DIR) fclean
endif
ifeq ($(USE_LIBFT), yes)
	@printf "\033[2K\r$(RED)→ Cleaning Libft...$(RESET)"
	@$(MAKE) --no-print-directory -C $(LIB_DIR)/$(LIBFT_DIR) fclean
endif

re: fclean all

# ------------------------------------------------------------------------------
# Cibles phony
# ------------------------------------------------------------------------------
.PHONY: all clean fclean re bonus
