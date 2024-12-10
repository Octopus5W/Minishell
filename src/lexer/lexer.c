#include "../../include/minishell.h"

int	skip_quote(char *s)
{
	int	i;

	i = 1;
	while (s && s[i] && s[i] != s[0] && s[i - 1] != '\\')
		i++;
	return (i);
}

int	skip_word(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '<' && s[i] != '>' && s[i] != '|')
		i++;
	if (i != 0 && (s[i] == '<' || s[i] == '>' || s[i] == '|'))
		i--;
	return (i);
}

t_token	*token_init(t_type type, char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value); // have to dup here
	return (token);
}

void	token_free(t_token *tokens)
{
	t_token	*next;

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

t_token	*token_add(t_token *tokens, t_type type, char *value)
{
	t_token	*new;
	t_token	*ptr;

	if (!tokens)
		return (token_init(type, value));
	if (!tokens)
		return (NULL);
	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = value;
	new->prev = tokens;
	ptr = tokens;
	while (tokens->next)
		tokens = tokens->next;
	tokens->next = new;
	return (ptr);
}

t_token	*token_delete(t_token *token)
{
	t_token	*prev;
	t_token	*next;

	free(token->value);
	token->value = NULL;
	prev = token->prev;
	next = token->next;
	free(token);
	token = NULL;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	return (next);
}

t_token	*lexer(char *cmd)
{
	t_token	*tokens;
	t_token	*check_malloc;
	int		i;
	int		j;

	tokens = NULL;
	i = 0;
	while (cmd && cmd[i])
	{
		if ((cmd[i] == '\'' || cmd[i] == '\"'))
		{
			j = skip_quote(cmd + i);
			check_malloc = token_add(tokens, WORD, ft_substr(cmd + i, 0, j));
			i += j;
		}
		else if (cmd[i] == '|')
			check_malloc = token_add(tokens, PIPE, "|");
		else if (cmd[i] == '<' && cmd[i + 1] == '<')
		{
			check_malloc = token_add(tokens, HEREDOC, "<<");
			i++;
		}
		else if (cmd[i] == '>' && cmd[i + 1] == '>' && i + 1)
		{
			check_malloc = token_add(tokens, APPEND, ">>");
			i++;
		}
		else if (cmd[i] == '<')
			check_malloc = token_add(tokens, IN, "<");
		else if (cmd[i] == '>')
			check_malloc = token_add(tokens, OUT, ">");
		else
		{
			j = skip_word(cmd + i);
			check_malloc = token_add(tokens, WORD, ft_substr(cmd + i, 0, j));
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
