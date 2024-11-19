#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "readline/readline.h"
# include <dirent.h>
# include <readline/history.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <unistd.h>
# define BUFSIZE 1024;

// typedef enum e_type
// {
// 	PIPE,
// 	REDIR_IN,
// 	REDIR_OUT
// }						t_type;

// typedef struct s_token
// {
// 	char				**cmd;
// 	t_type				type;
// 	struct s_token		*prev;
// 	struct s_token		*next;
// }						t_token;

typedef struct s_astnode
{
	char				**cmd;
	// t_type				type;
	char				**envdup;
	struct s_astnode	*left;
	struct s_astnode	*right;
}						t_astnode;

typedef struct s_data
{
	char				**envdup;
	bool				isbuiltin;
	char				*str;
	t_astnode			*node;
}						t_data;

int						init(t_data *data, char **env);
void					fake_parser(t_data *data);
int						echo(char **cmd);
void					execution_cmd(char **env, char **s);
/* UTILS */
char					**ft_split(char const *s, char c);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
size_t					ft_strlen(const char *s);
int						ft_strncmp(const char *s1, const char *s2, size_t n);

#endif