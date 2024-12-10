#include "../include/minishell.h"

void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		printf("%s	%d\n", current->value, current->type);
		// printf("%s	%s\n", current->name, current->var);
		current = current->next;
	}
}

int	main(void)
{
	char	*line;
	t_token	*tokens;
	t_ast	*ast;

	tokens = NULL;
	ast = NULL;
	memset(&ast, 0, sizeof(t_ast));
	line = "date | wc -c > file";
	tokens = lexer(line);
	print_tokens(tokens);
	ast = parse_tokens(&tokens);
	return (0);
}
