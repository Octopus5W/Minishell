#include "../include/minishell.h"

int	main(int argc, char *argv[], char **env)
{
	char	*line;
	t_data	data;

	(void)argc;
	(void)argv;

	line = "echo hello";
	if (duplicate_env(&data, env))
		return (1);
	data.tokens = lexer(line);
	data.ast = parse_tokens(&data.tokens);
	execution(&data, data.ast);
	return (0);
}
