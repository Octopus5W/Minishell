NAME = minishell

# Dossier des fichiers sources
SRCS = src/main.c src/init.c \
       src/env_var/env_var.c src/execution/execution.c \
       src/parsing/syntax_checker.c src/tokenaizer/tokenaizer.c

# Dossier des fichiers objets
OBJ_DIR = obj

# Crée la liste des fichiers objets, en les plaçant dans le répertoire obj/
OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

# Cibles
all: $(NAME)

$(NAME): $(OBJS)
	make -C libft/
	cc -Wall -Wextra -Werror -o $@ $^ libft/libft.a -lreadline

# Règle pour compiler les fichiers .c en .o
$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)  # Crée tous les répertoires nécessaires dans obj/
	cc -Wall -Wextra -Werror -c -g $< -o $@

# Clean pour supprimer les fichiers objets
clean:
	rm -rf $(OBJS)
	make clean -C libft/

# Fclean pour supprimer les fichiers objets et l'exécutable
fclean: clean
	rm -rf $(NAME)
	make fclean -C libft/

# Rebuild complet
re: fclean all
