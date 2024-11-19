NAME = minishell

SRCS = main.c parsing/syntax_checker.c parsing/tokenaizer.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft/
	mv syntax_checker.o tokenaizer.o parsing
	cc -Wall -Wextra -Werror -o $@ $^ libft/libft.a

.c.o:
	cc -Wall -Wextra -Werror -c -g $< 

clean:
	rm -rf $(OBJS)
	make clean -C libft/

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft/

re: fclean all