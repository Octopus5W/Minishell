#include "../include/minishell.h"

const char	*get_token_type_name(t_type type)
{
	const char	*token_type_names[7];

	token_type_names[0] = "WORD";
	token_type_names[1] = "PIPE";
	token_type_names[2] = "IN";
	token_type_names[3] = "OUT";
	token_type_names[4] = "APPEND";
	token_type_names[5] = "HEREDOC";
	token_type_names[6] = "VAR";
	if (type >= 0 && type < 7)
		return (token_type_names[type]);
	return ("UNKNOWN");
}

void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		printf("%s	%s\n", current->value, get_token_type_name(current->type));
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
	memset(&tokens, 0, sizeof(t_token));
	line = "date";
	tokens = lexer(line);
	//print_tokens(tokens);
	//ast = parse_tokens(&tokens);
	return (0);
}
