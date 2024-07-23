CFLAGS = -Wall -Wextra -Werror -g
DEPS = ./include/pipex.h
DEPS_BONUS = ./include/pipex_bonus.h
RM = rm -rf
SRC_DIR = ./src/
BONUS_DIR = ./src_bonus/
LIBFT_DIR = ./libs/libft
NAME = pipex
NAME_BONUS = pipex_bonus
SRC =  $(SRC_DIR)main.c $(SRC_DIR)errors_and_free.c $(SRC_DIR)set_files.c $(SRC_DIR)pipex.c $(SRC_DIR)utils.c
BONUS_SRC = $(BONUS_DIR)main_bonus.c $(BONUS_DIR)errors_bonus.c $(BONUS_DIR)handle_files_bonus.c $(BONUS_DIR)pipex_bonus.c $(BONUS_DIR)handle_here_doc_bonus.c $(BONUS_DIR)utils_bonus.c

# -- COLORS -- #
BLACK=\033[0;30m# Black
RED=\033[0;31m# Red
GREEN=\033[0;32m# GREEN
YELLOW=\033[0;33m# YELLOW
BLUE=\033[0;34m# BLUE
PURPLE=\033[0;35m# PURPLE
CYAN=\033[0;36m# CYAN
WHITE=\033[0m# WHITE

all: $(NAME)

bonus: $(NAME_BONUS)

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

$(NAME): $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "$(GREEN)Compilation successful. Library: $(NAME) $(WHITE)"

$(NAME_BONUS): $(BONUS_OBJ)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(BONUS_OBJ) -L$(LIBFT_DIR) -lft -o $(NAME_BONUS)
	@echo "$(GREEN)Compilation successful. Library: $(NAME_BONUS) $(WHITE)"

# création des fichiers objets à partir des fichiers source.
%.o: %.c $(DEPS_BONUS) $(DEPS) 
	@$(CC) -c -o $@ $< -I$(LIBFT_DIR) $(CFLAGS)

# supprime les fichiers objets. #
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(RM) $(OBJ) $(BONUS_OBJ)
	@echo "$(CYAN)Object files cleaned successfully. Library: $(NAME) $(WHITE)"
	@echo "--------------------------------------------------------"

# supprime les fichiers objets et la bibliothèque.
fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@echo "$(CYAN)Library cleaned successfully. Library: $(NAME) $(WHITE)"
	@echo "--------------------------------------------------------"

re: fclean all

val: all
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --trace-children=yes ./pipex infile "grep "Hello"" "wc -l" outfile

# indique que 'all', 'clean', 'fclean' et 're' ne sont pas des fichiers. #
.PHONY: all bonus clean fclean re
