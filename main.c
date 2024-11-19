#include "minishell.h"

int main ()
{
	t_token* tokens;
	char *s = "echo -n >lol | echo <lol -n <mdr";
	int i = 0;

	if (!quote_is_closed(s))
		return (0);
	tokens = tokenaizer(s);
	while (tokens)
	{
		i++;
		printf("Token %d:\ntype: %i\nvalue: %s\nnext: %p\n----------------------------------\n", i, tokens->type, tokens->value, tokens->next);
		tokens = tokens->next;
	}
}