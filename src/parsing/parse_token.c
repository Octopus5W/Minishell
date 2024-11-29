#include "../../include/minishell.h"

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
	char *word;

	i = 0;
	word = NULL;
	if (!s && !s[i])
		return (NULL);
	while (s && s[i] && (s[i] != ' ' || (s[i] >= 7 && s[i] <= 13)))
		i++;
	while (s && s[i] && (s[i] == ' ' || (s[i] >= 7 && s[i] <= 13)))
		i++;
	if(!s[i])
		return (NULL);
	if (s[i])
	{
		word = ft_strdup(s + i);
		if (!word)
			return (free(s), NULL);
	}
	free(s);
	return (word);
}

t_token* token_merge(t_token *token, t_token *merger)
{
	char *word;

	if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_REDIR_APPEND || token->type == TOKEN_REDIR_HEREDOC)
	{
		word = ft_strjoin(token->value, take_first_word(merger->value));
		if (word == NULL)
			return (NULL);
		merger->value = take_second_part(merger->value);
		if (merger->value == NULL)
			token_delete(merger);
	}
	else if (token->type == TOKEN_WORD)
	{
	 	word = ft_strjoin(token->value, merger->value);
		if (token->type == TOKEN_WORD)
			token_delete(merger);
	}
	else
		return (NULL);
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
			if (ptr->next && ptr->next->type == TOKEN_WORD)
			{
				token_merge(ptr, ptr->next);
				printf("Token redir:\ntype: %i\nvalue: %s\nprev: %p\nnext: %p\n----------------------------------\n", tokens->type, tokens->value, tokens->prev, tokens->next);
				if (!ptr)
					return (NULL);
			}
			else
			 {
				printf("bash: syntax error near unexpected token\n");
				return (NULL);
			 }
		}
		if (ptr)
			ptr = ptr->next;
		printf("Token redir 2:\ntype: %i\nvalue: %s\nprev: %p\nnext: %p\n----------------------------------\n", tokens->type, tokens->value, tokens->prev, tokens->next);
		
	}
	return (tokens);
}

t_token* word_merge(t_token *token, t_token *merger)
{
	char *word;
	char *tmp;

	tmp = ft_strjoin(token->value, " ");
	if (!tmp)
		return (NULL);
	word = ft_strjoin(tmp, merger->value);
	if (!word)
		return (free(tmp), NULL);
	free(token->value);
	token->value = word;
	free(tmp);
	token_delete(merger);
	return (token);
}

t_token* word_checker(t_token *tokens)
{
	t_token *ptr;
	t_token *word;

	ptr = tokens;
	while (ptr)
	{
		if (ptr->type == TOKEN_WORD)
		{
			word = ptr;
			ptr = ptr->next;
			while (ptr->next && ptr->next->type != TOKEN_PIPE)
			{
				if (ptr->next->type == TOKEN_WORD)
					ptr = word_merge(word, ptr);
				if (!ptr)
					return (NULL);
				if (ptr)
					ptr = ptr->next;
			}
		}
		if (ptr)
			ptr = ptr->next;
	}
	return (tokens);
}

char **parse_token(t_token *tokens)
{
	char **cmds;
	int count_pipe;

	count_pipe = pipe_count(tokens);
	cmds = malloc(sizeof(char *) * (count_pipe + 2));
	if (!cmds)
		return (NULL);
	cmds[count_pipe + 1] = NULL;
	tokens = redir_checker(tokens);
	if (!tokens)
	{
		free(cmds);
		return (NULL);
	}
	// tokens = word_checker(tokens);
	// if (!tokens)
	// {
	// 	free(cmds);
	// 	return (NULL);
	// }
	return(cmds);
}