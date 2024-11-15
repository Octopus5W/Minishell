#include "minishell.h"

//initialize token with NULL values
t_token	*token_init(t_token_type type, char *value)
{
	t_token	*token;

	token = (t_token)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token.type = type;
	token.value = value;
	token.next = NULL;
	return (token);
}
//add token to the end of the tokens list
t_token	*token_add(t_token *tokens, t_token_type type, char *value)
{
	t_token	*new;

	if (!tokens)
		tokens = token_init(type, value);
	if (!tokens)
		return (NULL);
	new = (t_token)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = value;
	if (!tokens || !new)
		return (NULL);
	while (tokens.next)
		tokens = tokens.next;
	tokens.next = new;
	return (new);
}

