#include "../../include/minishell.h"

// skip quote et skip word ne fonctionne pas avec plusieurs "\" 
int	skip_quote(char *s)
{
	int i;
	int j;
	i = 1;
	while (s && s[i] && s[i] != s[0])
	{
		if (s[i] == '\\')
		{
			j = 1;
			while (s[i] == '\\')
				j++;
			if (s[i] && j % 2 == 0 && s[i + 1] == s[0])
				return (j + i + 1);
			i += j;
		}
		i++;
	}
	return (i);
}

int skip_word(char *s)
{
	int i;

	i = 0;
	while (s && s[i] && s[i] != '<' && s[i] != '>' && s[i] != '|' && s[i] != ' ' && (s[i] < 7 || s[i] > 15) && s[i] != '\'' && s[i] != '\"')
		i++;
	if (s[i] == '\'' || s[i] == '\"')
		i += skip_quote(s + i);
	if (i != 0 && (s[i] == '<' || s[i] == '>' || s[i] == '|' || s[i] == ' ' || (s[i] >= 7 && s[i] <= 15) || !s[i]))
		return(i);
	else
		i += skip_word(s + i);
	return (i);
}

//initialize token with NULL values
t_token	*token_init(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->prev = NULL;
	token->next = NULL;
	return (token);
}

void	token_free(t_token *tokens)
{
	t_token *next;

	while (tokens && tokens->next)
	{
		tokens->prev = NULL;
		next = tokens->next;
		free(tokens->value);
		tokens->value = NULL;
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
	new->prev = tokens;
	new->next = NULL;
	ptr = tokens;
	while (tokens->next)
		tokens = tokens->next;
	tokens->next = new;
	return (ptr);
}

t_token* token_delete(t_token *token) // no need
{
	t_token *prev;
	t_token *next;

	free(token->value);
	token->value = NULL;
	prev = token->prev; // token->next->prev
	next = token->next; // token->next->next
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	free(token);
	token = NULL;
	return (next);
}

t_token*	tokenaizer(char *cmd)
{
	t_token *tokens;
	t_token	*check_malloc;
	int cursor;
	int j;

	tokens = NULL;
	cursor = 0;
	while (cmd && cmd[cursor])
	{
		if (cmd[cursor] == '|')
			check_malloc = token_add(tokens, TOKEN_PIPE, NULL);
		else if (cmd[cursor] == '<' && cmd[cursor + 1] == '<')
		{
			check_malloc = token_add(tokens, TOKEN_REDIR_HEREDOC, NULL);
			cursor++;
		}
		else if (cmd[cursor] == '>' && cmd[cursor + 1] == '>' && cursor + 1)
		{
			check_malloc = token_add(tokens, TOKEN_REDIR_APPEND, NULL);
			cursor++;
		}
		else if (cmd[cursor] == '<')
			check_malloc = token_add(tokens, TOKEN_REDIR_IN, NULL);
		else if (cmd[cursor] == '>')
			check_malloc = token_add(tokens, TOKEN_REDIR_OUT, NULL);
		else if (cmd[cursor] != ' ' && (cmd[cursor] < 7 || cmd[cursor] > 15)) 
		{
			j = skip_word(cmd + cursor);
			check_malloc = token_add(tokens, TOKEN_WORD, ft_substr(cmd + cursor, 0, j));
			cursor += j - 1;
		}
		cursor++;
		if (!check_malloc && cmd[cursor - 1] != ' ' &&  (cmd[cursor - 1] < 7 || cmd[cursor] > 15))
			return (token_free(tokens), NULL);
		else if (!tokens)
			tokens = check_malloc;
	}
	return (tokens);
}
