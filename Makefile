NAME = minishell

SRCS = src/main.c \
    src/lexer/lexer.c src/lexer/tmp_functions.c \
	src/parser/parser.c src/parser/utils_parser.c 

OBJ_DIR = obj

OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft/
	cc -Wall -Wextra -Werror -o $@ $^ libft/libft.a -lreadline

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)  # Crée tous les répertoires nécessaires dans obj/
	cc -Wall -Wextra -Werror -c -g $< -o $@

clean:
	rm -rf $(OBJS)
	make clean -C libft/

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft/

re: fclean all