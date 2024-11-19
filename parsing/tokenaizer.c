#include "../minishell.h"

//initialize token with NULL values
t_token	*token_init(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

void	token_free(t_token *tokens)
{
	t_token *next;

	while (tokens && tokens->next)
	{
		next = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = next;
	}
}

//add token to the end of the tokens list
t_token	*token_add(t_token *tokens, t_token_type type, char *value)
{
	t_token	*new;
	t_token *ptr;

	if (!tokens)
		return (token_init(type, value));
	if (!tokens)
		return (NULL);
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = value;
	new->next = NULL;
	ptr = tokens;
	while (tokens->next)
		tokens = tokens->next;
	tokens->next = new;
	return (ptr);
}

int	skip_quote(char *s)
{
	int i;

	i = 1;
	while (s && s[i] && s[i] != s[0] && s[i - 1] != '\\')
		i++;
	return (i);
}

int skip_word(char *s)
{
		int i;

	i = 0;
	while (s && s[i] && s[i] != '<' && s[i] != '>' && s[i] != '|')
		i++;
	if (i != 0 && (s[i] == '<' || s[i] == '>' || s[i] == '|'))
		i--;
	return (i);
}

t_token*	tokenaizer(char *cmd)
{
	t_token *tokens;
	t_token	*check_malloc;
	int i;
	int j;

	tokens = NULL;
	i = 0;
	while (cmd && cmd[i])
	{
		if ((cmd[i] == '\'' || cmd[i] == '\"'))
		{
			j = skip_quote(cmd + i);
			check_malloc = token_add(tokens, TOKEN_WORD, ft_substr(cmd + i, 0, j));
			i += j;
		}
		else if (cmd[i] == '|')
			check_malloc = token_add(tokens, TOKEN_PIPE, NULL);
		else if (cmd[i] == '<' && cmd[i + 1] == '<')
		{
			check_malloc = token_add(tokens, TOKEN_REDIR_HEREDOC, NULL);
			i++;
		}
		else if (cmd[i] == '>' && cmd[i + 1] == '>' && i + 1)
		{
			check_malloc = token_add(tokens, TOKEN_REDIR_APPEND, NULL);
			i++;
		}
		else if (cmd[i] == '<')
			check_malloc = token_add(tokens, TOKEN_REDIR_IN, NULL);
		else if (cmd[i] == '>')
			check_malloc = token_add(tokens, TOKEN_REDIR_OUT, NULL);
		else
		{
			j = skip_word(cmd + i);
			check_malloc = token_add(tokens, TOKEN_WORD, ft_substr(cmd + i, 0, j));
			i += j;
		}
		if (!check_malloc)
			return (token_free(tokens), NULL);
		else
			tokens = check_malloc;
		i++;
	}
	return (tokens);
}
