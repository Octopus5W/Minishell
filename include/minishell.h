#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "readline/readline.h"
# include <dirent.h>
# include <fcntl.h>
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

// structure for the environment variables list copy
typedef struct s_envlist
{
	char *name; // only the name of the variable
	char *var;  // only the content of the variable
	char *raw;  // name + variable
	struct s_envlist	*prev;
	struct s_envlist	*next;
}						t_envlist;

typedef struct s_ast_node
{
	t_type				type;
	char				*value;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

typedef struct s_token
{
	t_type				type;
	char				*value;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;

typedef struct s_data
{
	char **env_array;    // duplicate the env variables
	t_envlist *env_list; // environment variables list copy
}						t_data;

// init
int						init(t_data *data, char **env);

// ast
int						build_ast(t_token *tokens);

// environment variables
int						env_list(t_data *data, char **env);
int						env_array(t_data *data, char **env);
t_envlist				*create_node(char *var);
char					*extract_var(char *str);
char					*extract_name(char *str);
char					*env_expand(t_data *data, char *to_expand);
t_envlist				*last_node(t_envlist *env_list);

// builtins
void					builtins(t_data *data);
int						echo(char **cmd);
int						export(t_data *data, char **cmd);
int						unset(t_data *data, char **cmd);
void					envv(t_data *data);

// redirections
int						redir_out(t_data *data, char **cmd, char *file);
int						sh_pipe(t_data *data, char ***c);

// execution
int						execution_cmd(t_data *data, char **cmd);

// free
void					free_array(char **strs, int i);
void					free_list(t_data *data);

// utils
char					**ft_split(char const *s, char c);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
size_t					ft_strlen(const char *s);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_strslen(char **strs);

#endif