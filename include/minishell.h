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

typedef struct s_data	t_data;

typedef enum e_type
{
	WORD,
	PIPE,
	IN,
	OUT,
	APPEND,
	HEREDOC,
	VAR
}						t_type;

typedef struct s_token
{
	t_type				type;
	char				*value;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;

typedef struct s_ast
{
	t_type				type;
	char				**args;
	bool				is_builtin;
	struct s_ast		*left;
	struct s_ast		*right;
}						t_ast;

// syntax_checker
int						quote_is_closed(const char *s);

// lexer
t_token					*lexer(char *cmd);
t_token					*token_delete(t_token *tokens);
t_token					*token_add(t_token *tokens, t_type type, char *value);
void					token_free(t_token *tokens);

// parser
t_ast					*parse_tokens(t_token **tokens);
t_ast					*parse_pipeline(t_token **tokens);
t_ast					*parse_redirection(t_token **tokens);
t_ast					*create_file_node(t_token *token);
t_ast					*parse_command(t_token **tokens);

t_ast					*new_ast_node(t_type type);
void					free_ast(t_ast *node);
t_ast					*create_and_link_redirection(t_token **tokens,
							t_token *tmp);
int						count_command_arguments(t_token *current);
void					fill_command_arguments(t_ast *command_node,
							t_token **tokens, int arg_count);

// utils
char					**ft_split(char const *s, char c);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
size_t					ft_strlen(const char *s);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_strslen(char **strs);

#endif