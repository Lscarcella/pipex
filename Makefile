CFLAGS = -Wall -Wextra -Werror -g
DEPS = ./include/pipex.h
RM = rm -rf
# CC = GCC
SRC_DIR = ./src/
LIBFT_DIR = ./libs/libft
NAME = pipex
SRC =  $(SRC_DIR)main.c $(SRC_DIR)handle_here_doc.c $(SRC_DIR)utils.c

# -- COLORS -- # 
BLACK=\033[0;30m# Black
RED=\033[0;31m# Red
GREEN=\033[0;32m# GREEN
YELLOW=\033[0;33m# YELLOW	
BLUE=\033[0;34m# BLUE
PURPLE=\033[0;35m# PURPLE
CYAN=\033[0;36m# CYAN
WHITE=\033[0m# WHITE

all : $(NAME)

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "$(GREEN)Compilation successful. Library: $(NAME) $(WHITE)"

# création des fichiers objets à partir des fichiers source. 
%.o: %.c $(DEPS)
	@$(CC) -c -o $@ $< -I$(LIBFT_DIR) $(CFLAGS)

# supprime les fichiers objets. #
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(RM) $(OBJ)
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
	valgrind --leak-check=full --show-leak-kinds=all ./pipex here_doc stop 1 2 outfile


# indique que 'all', 'clean', 'fclean' et 're' ne sont pas des fichiers. #
.PHONY: all clean fclean re