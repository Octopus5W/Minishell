#include "../include/minishell.h"

int	main(void)
{
	char	*line;
	t_token	*tokens;
	t_ast	*ast;

	tokens = NULL;
	ast = NULL;
	line = "echo hello";
	tokens = lexer(line);
	print_tokens(&tokens);
	ast = parse_tokens(&tokens);
	print_ast(ast, 0);
	return (0);
}
