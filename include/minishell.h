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

typedef enum e_type
{
	WORD,
	PIPE,
	IN,
	OUT,
	APPEND,
	HEREDOC,
	VAR,
	END
}					t_type;

typedef struct s_token
{
	t_type			type;
	char			*lexeme;
	size_t			i;
	bool			inquotes;
	struct s_token	*next;
}					t_token;

typedef struct s_ast
{
	t_type			type;
	char			**command;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef struct s_env
{
	char			*name;
	char			*var;
	char			*line;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	t_token			*tokens;
	t_ast			*ast;
	t_env			*env_list;
}					t_data;

// INIT
int					duplicate_env(t_data *data, char **env);
t_env				*create_node(char *var);

// LEXER
t_token				*lexer(char *cmd);
// temp functions
void				print_tokens(t_token **tokens);
const char			*get_token_type_name(t_type type);

// PARSER
t_ast				*parse_tokens(t_token **tokens);
t_ast				*parse_pipeline(t_token **tokens);
t_ast				*parse_redirection(t_token **tokens);
t_ast				*create_file_node(t_token *token);
t_ast				*parse_command(t_token **tokens);
t_ast				*new_ast_node(t_type type);
// void					free_ast(t_ast *node);
t_ast				*create_and_link_redirection(t_token **tokens,
						t_token *tmp);
int					count_command_arguments(t_token *current);
void				fill_command_arguments(t_ast *command_node,
						t_token **tokens, int arg_count);
// temp functions
void				print_ast(t_ast *node, int depth);

// EXEC
int					execution(t_data *data, t_ast *ast);
int					command(t_data *data, char **cmd);

// BUILTINS
int					echo(char **cmd);
int					pwd(void);
void				env(t_env *env_list);
int					export(t_data *data, char **cmd);
int					unset(t_data *data, char **cmd);
int					cd(char **cmd);

// utils
char				**ft_split(char const *s, char c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strslen(char **strs);
void				ft_bzero(void *s, size_t n);

#endif
