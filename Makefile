NAME = minishell

SRCS = main.c

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