#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include "libft/libft.h"

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
}   t_token_type;

// token structure for tokenization
typedef struct s_token
{
	t_token_type type;
	char        *value;
	struct s_token *next;
}   t_token;

// structure for the AST branch
typedef struct s_ast_node
{
	t_token_type type;
	char **args;
	struct s_ast_node *left;
	struct s_ast_node *right;
}   t_ast_node;

//syntax_checker
int quote_is_closed(const char *s);

//tokenaizer
t_token	*tokenaizer(char *cmd);
t_token* token_delete(t_token *tokens);
t_token	*token_add(t_token *tokens, t_token_type type, char *value);
void token_free(t_token *tokens);

#endif