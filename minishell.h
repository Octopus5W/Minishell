#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>

typedef struct s_cmd
{
    char    **cmd;
    char    *path;
}           t_cmd;

void    cmd(char **env, char **s);

/* UTILS */
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

#endif