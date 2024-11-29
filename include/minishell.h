#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "readline/readline.h"
# include <dirent.h>
# include <readline/history.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define BUFSIZE 1024;

typedef struct s_data	t_data;

// enum for the type of node in tokenization and the AST
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_ENV_VAR
}						t_token_type;

// token structure for tokenization
typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;

// structure for the AST branch
typedef struct s_ast
{
	t_token_type		type;
	char				*cmd;
	char				**args;
	bool				isbuiltin;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast;

typedef struct s_data
{
	char **env_array; // duplicate the env variables
	t_list *env_list; // env variable dup linked list
	t_token *tokens;  // link to t_token node
	t_ast *node;     // link to t_ast node
}						t_data;

// builtin
void					builtins(t_data *data);
int						echo(char **cmd);

// env_var

// execution
int						execution_cmd(t_data *data);

// syntax_checker
int						quote_is_closed(const char *s);

// parsing
char **parse_token(t_token *tokens);

// tokenaizer
t_token					*tokenaizer(char *cmd);
t_token					*token_delete(t_token *tokens);
t_token					*token_add(t_token *tokens, t_token_type type,
							char *value);
void					token_free(t_token *tokens);


// init
int						init(t_data *data, char **env);


// utils
char					**ft_split(char const *s, char c);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
size_t					ft_strlen(const char *s);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_strslen(char **strs);

#endif