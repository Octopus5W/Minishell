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

t_ast	*ast_add(t_ast *node, t_token_type type, char **args)
{
	t_ast	*new;

	new = ast_init(type, args);
	if (!new)
		return (NULL);
	if (node->right)
	{
		new->left = node->right;
		node->right = new;
	}
	else
		node->right = new;
	return (node);
}

void	ast_free(t_ast *node)
{
	if (node->left)
		ast_free(node->left);
	if (node->right)
		ast_free(node->right);
	free(node->args);
	free(node);
}




t_ast	*ast_build(t_token *tokens)
{
	t_ast	*node;
	t_token	*ptr;
	char	**args;
	int		i;

	node = NULL;
	ptr = tokens;
	while (ptr)
	{
		i = 0;
		while (ptr && ptr->type != TOKEN_PIPE)
		{
			i++;
			ptr = ptr->next;
		}
		if (ptr->type == TOKEN_PIPE)
			get_before(tokens, i, args);
	}
	return (node);
}



