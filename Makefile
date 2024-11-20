NAME = minishell

SRCS = src/main.c src/init.c \
	src/env_var/env_var.c src/execution/execution.c src/parsing/fake_parser.c 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft/
	cc -Wall -Wextra -Werror -O3 -o $@ $^ libft/libft.a -lreadline

.c.o:
	cc -Wall -Wextra -Werror -O3 -g -c $< 

clean:
	rm -rf $(OBJS)
	make clean -C libft/

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft/

re: fclean all