#include "minishell.h"

char* take_first_word(char *s)
{
	int i;

	i= 0;
	if (!s && !s[i])
		return (NULL);
	while (s && s[i])
	{
		if (s[i] == ' ')
			return (ft_substr(s, 0, i));
		i++;
	}
	return (ft_strdup(s));
}

char *take_second_part(char *s)
{
	int i;
	i = 0;
	if (!s && !s[i])
		return (NULL);
	while (s && s[i] && (s[i] == ' ' || (s[i] >= 7 && s[i] <= 13)))
		i++;

	if(!s[i])
		return (NULL);
	return (ft_strdup(s + i));
}

t_token* token_merge(t_token *token, t_token *merger)
{
	char *word;

	if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_REDIR_APPEND || token->type == TOKEN_REDIR_HEREDOC)
	{
		word = ft_strjoin(token->value, take_first_word(merger->value));
		merger = take_second_part(merger->value);
	}
	else if (token->type == TOKEN_WORD)
	 	word = ft_strjoin(token->value, merger->value);
	if (!merger->value || token->type == TOKEN_WORD)
		token_delete(merger);
	free(token->value);
	token->value = word;
	return (token);
}

int pipe_count(t_token *tokens)
{
	int count;

	count = 0;
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

t_token* redir_checker(t_token *tokens)
{
	t_token *ptr;

	ptr = tokens;
	while (ptr)
	{
		if (ptr->type == TOKEN_REDIR_IN || ptr->type == TOKEN_REDIR_OUT
			|| ptr->type == TOKEN_REDIR_APPEND || ptr->type == TOKEN_REDIR_HEREDOC)
		{
			if (ptr->next->type == TOKEN_WORD)
				ptr = token_merge(ptr, ptr->next);
			else
				return (NULL);
		}
		ptr = ptr->next;
	}
	return (tokens);
}

// char **parse_token(t_token *tokens)
// {

// }