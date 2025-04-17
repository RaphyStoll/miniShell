# ------------------------------------------------------------------------------
# Configuration principale
# ------------------------------------------------------------------------------

USE_GNL = no
USE_PRINTF = no
USE_LIBFT = no
USE_BONUS = no

NAME        = output/libft.a
NAME_BONUS  = output/libft_bonus.a

CC          = gcc
CFLAGS      = -g -Wall -Wextra -Werror

MKDIR       = mkdir -p
RM          = rm -f

BLACK       = \033[0;30m
RED         = \033[0;91m
GREEN       = \033[0;92m
YELLOW      = \033[0;93m
BLUE        = \033[0;94m
MAGENTA     = \033[0;95m
CYAN        = \033[0;96m
WHITE       = \033[0;97m
BOLD        = \033[1m
UNDERLINE   = \033[4m
RESET       = \033[0m

SRC_DIR     = source
MAIN_DIR    = $(SRC_DIR)/main
BONUS_DIR   = $(SRC_DIR)/bonus

OBJ_DIR     = objects
MAIN_OBJ    = $(OBJ_DIR)/main
BONUS_OBJ   = $(OBJ_DIR)/bonus

OUTPUT_DIR  = output

LIB_DIR       = lib
FT_PRINTF_DIR = ft_printf
GNL_DIR       = gnl
LIBFT_DIR     = libft

FT_PRINTF_LIB = $(LIB_DIR)/$(FT_PRINTF_DIR)/libftprintf.a
GNL_LIB       = $(LIB_DIR)/$(GNL_DIR)/libgnl.a
LIBFT_LIB     = $(LIB_DIR)/$(LIBFT_DIR)/libft.a

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

MAIN_SRC = \
	ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint \
	ft_strlen ft_memset ft_bzero ft_memcpy ft_memmove \
	ft_strlcpy ft_strlcat ft_toupper ft_tolower ft_strchr \
	ft_strrchr ft_strcmp ft_strncmp ft_memchr ft_memcmp \
	ft_strnstr ft_atoi ft_calloc ft_strdup ft_strndup \
	ft_substr ft_strjoin ft_strtrim ft_split ft_itoa \
	ft_strmapi ft_striteri ft_putchar_fd ft_putstr_fd \
	ft_putendl_fd ft_putnbr_fd

MAIN_SRCS = $(addprefix $(MAIN_DIR)/, $(addsuffix .c, $(MAIN_SRC)))
MAIN_OBJS = $(addprefix $(MAIN_OBJ)/, $(addsuffix .o, $(MAIN_SRC)))

BONUS_SRC = \
	ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast ft_lstadd_back \
	ft_lstdelone ft_lstclear ft_lstiter ft_lstmap

BONUS_SRCS = $(addprefix $(BONUS_DIR)/, $(addsuffix .c, $(BONUS_SRC)))
BONUS_OBJS = $(addprefix $(BONUS_OBJ)/, $(addsuffix .o, $(BONUS_SRC)))

# ------------------------------------------------------------------------------
# Cibles principales
# ------------------------------------------------------------------------------
all: $(ALL_LIBS) $(NAME)

ifeq ($(USE_BONUS), yes)
bonus: $(ALL_LIBS) $(NAME_BONUS)
endif

$(NAME): $(MAIN_OBJS) $(BONUS_OBJS) | $(OUTPUT_DIR)
	@printf "\033[2K\r$(CYAN)→ Archiving objects for the main build...$(RESET)"
	@ar rcs $@ $(MAIN_OBJS) $(BONUS_OBJS)
	@printf "\033[2K\r$(BOLD)$(GREEN)✔ Finished building $(NAME)$(RESET)\n"

$(NAME_BONUS): $(BONUS_OBJS) | $(OUTPUT_DIR)
	@printf "\033[2K\r$(CYAN)→ Archiving objects for the bonus build...$(RESET)"
	@ar rcs $@ $(BONUS_OBJS)
	@printf "\033[2K\r$(BOLD)$(GREEN)✔ Finished building $(NAME_BONUS)$(RESET)\n"

# ------------------------------------------------------------------------------
# Création des répertoires
# ------------------------------------------------------------------------------
$(OUTPUT_DIR):
	@printf "\033[2K\r$(YELLOW)Creating output directory '$(OUTPUT_DIR)'$(RESET)"
	@$(MKDIR) $(OUTPUT_DIR)

$(MAIN_OBJ):
	@printf "\033[2K\r$(YELLOW)Creating object directory '$(MAIN_OBJ)'$(RESET)"
	@$(MKDIR) $(MAIN_OBJ)

$(BONUS_OBJ):
	@printf "\033[2K\r$(YELLOW)Creating object directory '$(BONUS_OBJ)'$(RESET)"
	@$(MKDIR) $(BONUS_OBJ)

# ------------------------------------------------------------------------------
# Compilation des sources principales
# ------------------------------------------------------------------------------
$(MAIN_OBJ)/%.o: $(MAIN_DIR)/%.c | $(MAIN_OBJ)
	@printf "\033[2K\r$(BLUE)Compiling $< → $@$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@printf "\033[2K\r$(GREEN)✔ Compiled $<$(RESET)\n"

# ------------------------------------------------------------------------------
# Compilation des sources bonus
# ------------------------------------------------------------------------------
$(BONUS_OBJ)/%.o: $(BONUS_DIR)/%.c | $(BONUS_OBJ)
	@printf "\033[2K\r$(MAGENTA)Compiling $< (bonus) → $@$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@printf "\033[2K\r$(GREEN)✔ Compiled $< (bonus)$(RESET)\n"

# ------------------------------------------------------------------------------
# Compilation des bibliothèques tierces
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
	@$(RM) $(MAIN_OBJS) $(BONUS_OBJS)
	@printf "\033[2K\r$(RED)→ Removing '$(OBJ_DIR)' directory...$(RESET)"
	@$(RM) -r $(OBJ_DIR)
	@printf "\033[2K\r$(GREEN)✔ Cleaned$(RESET)\n"

fclean: clean
	@printf "\033[2K\r$(RED)→ Removing executables...$(RESET)"
	@$(RM) $(NAME) $(NAME_BONUS)
	@printf "\033[2K\r$(RED)→ Cleaning libraries...$(RESET)"
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
	@printf "\033[2K\r$(RED)→ Removing '$(OUTPUT_DIR)' directory...$(RESET)"
	@$(RM) -r $(OUTPUT_DIR)
	@printf "\033[2K\r$(GREEN)✔ Full clean done$(RESET)\n"

re: fclean all

# ------------------------------------------------------------------------------
# Cibles phony
# ------------------------------------------------------------------------------
.PHONY: all clean fclean re bonus
