NAME = libft.a

SRCS = ft_atoi.c ft_atol.c ft_bzero.c ft_calloc.c ft_countdigits.c \
       ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
       ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
       ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
       ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strcmp.c\
       ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
       ft_strlcpy.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
       ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c \
       ft_toupper.c ft_strlen.c

SRCS_BONUS = ft_lstiter.c ft_lstlast.c ft_lstnew.c ft_lstsize.c \
             ft_lstadd_back.c ft_lstadd_front.c ft_lstdelone.c \
             ft_lstmap.c ft_lstclear.c

PRINTF = ft_printf/src/ft_printf.c ft_printf/src/format.c ft_printf/src/utils.c

GNL = get_next_line.c get_next_line_utils.c

SRCS_ADDED = ft_free.c ft_putnbr_base.c ft_strndup.c ft_strncpy.c ft_strslen.c

SRCS_ALL = $(SRCS) $(SRCS_BONUS) $(PRINTF) $(GNL) $(SRCS_ADDED)

OBJS = $(SRCS_ALL:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

$(OBJS): %.o: %.c
	cc -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
