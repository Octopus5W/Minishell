#include "../../include/minishell.h"

static t_token	*lstlast(t_token **tokens)
{
	t_token	*current;

	if (!tokens)
		return (NULL);
	if (!*tokens)
		return (*tokens);
	current = *tokens;
	while (current->next)
		current = current->next;
	return (current);
}

static void	add_back(t_token **tokens, t_token *new)
{
	t_token	*last;

	if (tokens == NULL || new == NULL)
		return ;
	if (*tokens == NULL)
	{
		*tokens = new;
		return ;
	}
	last = lstlast(tokens);
	last->next = new;
}

static t_token	*end_token(void)
{
	t_token	*end_token;

	end_token = ft_calloc(1, sizeof(t_token));
	if (!end_token)
		return (NULL);
	end_token->type = END;
	return (end_token);
}

static t_token	*pipe_token(void)
{
	t_token	*pipe_token;

	pipe_token = ft_calloc(1, sizeof(t_token));
	if (!pipe_token)
		return (NULL);
	pipe_token->type = PIPE;
	pipe_token->lexeme = "|";
	return (pipe_token);
}

static t_token	*in_token(void)
{
	t_token	*in_token;

	in_token = ft_calloc(1, sizeof(t_token));
	if (!in_token)
		return (NULL);
	in_token->type = IN;
	in_token->lexeme = "<";
	return (in_token);
}

static t_token	*heredoc_token(void)
{
	t_token	*heredoc_token;

	heredoc_token = ft_calloc(1, sizeof(t_token));
	if (!heredoc_token)
		return (NULL);
	heredoc_token->type = HEREDOC;
	heredoc_token->lexeme = "<<";
	return (heredoc_token);
}

static t_token	*out_token(void)
{
	t_token	*out_token;

	out_token = ft_calloc(1, sizeof(t_token));
	if (!out_token)
		return (NULL);
	out_token->type = OUT;
	out_token->lexeme = ">";
	return (out_token);
}

static t_token	*append_token(void)
{
	t_token	*append_token;

	append_token = ft_calloc(1, sizeof(t_token));
	if (!append_token)
		return (NULL);
	append_token->type = APPEND;
	append_token->lexeme = ">>";
	return (append_token);
}

void special(char *s, t_token **tokens, int *i)
{
	if (s[*i] == '|')
		add_back(tokens, pipe_token());
	else if (s[*i] == '<')
	{
		if (s[*i + 1] == '<')
		{
			add_back(tokens, heredoc_token());
			(*i)++;
		}
		else
			add_back(tokens, in_token());
	}
	else if (s[*i] == '>')
	{
		if (s[*i + 1] == '>')
		{
			add_back(tokens, append_token());
			(*i)++;
		}
		else
			add_back(tokens, out_token());
	}
}

int	inquotes(char *s)
{
	int	len;

	len = ft_strlen(s) - 1;
	if ((s[0] == '\"' && s[len] == '\"') || (s[0] == '\'' && s[len] == '\''))
		return (1);
	return (0);
}

int	word_token(char *s, t_token **tokens, int *i)
{
	t_token	*word_token;
	int		j;

	j = *i;
	while (s[j] && s[j] != ' ' && s[j] != '\t' && s[j] != '|' && s[j] != '<' && s[j] != '>')
		j++;
	word_token = ft_calloc(1, sizeof(t_token));
	if (!word_token)
		return (1);
	word_token->lexeme = ft_substr(s, *i, j - *i);
	if (!word_token->lexeme)
		return (1);
	if (word_token->lexeme[0] == '$')
		word_token->type = VAR;
	else
		word_token->type = WORD;
	if (inquotes(word_token->lexeme))
		word_token->inquotes = true;
	add_back(tokens, word_token);
	*i = j - 1;
	return (0);
}

t_token	*lexer(char *s)
{
	t_token	*tokens;
	int		i;

	i = 0;
	tokens = NULL;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		if (s[i] == '|' || s[i] == '<' || s[i] == '>')
			special(s, &tokens, &i);
		else
			if (word_token(s, &tokens, &i))
				return (NULL);
		i++;
	}
	add_back(&tokens, end_token());
	return (tokens);
}