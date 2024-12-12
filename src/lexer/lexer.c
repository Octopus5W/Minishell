#include "../../include/minishell.h"

t_token	*lstlast(t_token *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_token	*pipe_token(void)
{
	t_token	*pipe_token;

	pipe_token = ft_calloc(1, sizeof(t_token));
	if (!pipe_token)
		return (NULL);
	pipe_token->value = "|";
	pipe_token->type = PIPE;
	return (pipe_token);
}

t_token	*in_token(void)
{
	t_token	*in_token;

	in_token = ft_calloc(1, sizeof(t_token));
	if (!in_token)
		return (NULL);
	in_token->value = "<";
	in_token->type = IN;
	return (in_token);
}

t_token	*out_token(void)
{
	t_token	*out_token;

	out_token = ft_calloc(1, sizeof(t_token));
	if (!out_token)
		return (NULL);
	out_token->value = ">";
	out_token->type = OUT;
	return (out_token);
}

t_token	*heredoc_token(void)
{
	t_token	*heredoc_token;

	heredoc_token = ft_calloc(1, sizeof(t_token));
	if (!heredoc_token)
		return (NULL);
	heredoc_token->value = "<<";
	heredoc_token->type = HEREDOC;
	return (heredoc_token);
}

t_token	*append_token(void)
{
	t_token	*append_token;

	append_token = ft_calloc(1, sizeof(t_token));
	if (!append_token)
		return (NULL);
	append_token->value = ">>";
	append_token->type = APPEND;
	return (append_token);
}

void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*last;

	last = lstlast(*tokens);
	if (!last)
		*tokens = new_token;
	else
		last->next = new_token;
}

t_token	*lexer(char *input)
{
	t_token	*tokens;
	int		i;
	int		input_len;

	i = 0;
	input_len = (int)ft_strlen(input) - 1;
	while (input[i])
	{
		if (input[i] == '|')
			add_token(&tokens, pipe_token());
		if (i + 1 <= input_len)
			if (input[i] == '>' && !isspace(input[i + 1]))
				add_token(&tokens, out_token());
		if (i + 1 <= input_len)
			if (input[i] == '<' && input[i + 1] == '<')
				add_token(&tokens, heredoc_token());
		if (i + 1 <= input_len)
			if (input[i] == '<' && isspace(input[i + 1]))
				add_token(&tokens, in_token());
		if (i + 1 <= input_len)
			if (input[i] == '>' && input[i + 1] == '>')
				add_token(&tokens, append_token());
		i++;
	}
	return (0);
}

// date | wc -c >file