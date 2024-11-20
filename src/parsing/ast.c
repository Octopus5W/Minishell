#include "../../include/minishell.h"

t_ast	*ast_init(t_token_type type, char **args)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = args;
	node->left = NULL;
	node->right = NULL;
	return (node);
}