#include "minishell.h"

int main ()
{
	t_token* tokens/*, *tokensdeux*/;
	char *s = "echo -n >lol | echo <lol -n <mdr";
	int i = 0;

	if (!quote_is_closed(s))
		return (0);
	tokens = tokenaizer(s);
	// tokensdeux = tokens->next;
	while (tokens)
	{
		i++;
		printf("Token %d:\ntype: %i\nvalue: %s\nnext: %p\n----------------------------------\n", i, tokens->type, tokens->value, tokens->next);
		if (i%2 == 0)
		{
			tokens = token_delete(tokens);
		}
		else
			tokens = tokens->next;
	}
	i=0;
	// printf("\n\n\n");
	// while (tokensdeux)
	// {
	// 	i++;
	// 	printf("Token %d:\ntype: %i\nvalue: %s\nnext: %p\n----------------------------------\n", i, tokens->type, tokens->value, tokens->next);
	// 	tokensdeux = tokensdeux->next;
	// }
}