#include "../../include/minishell.h"

t_ast	*new_ast_node(t_type type)
{
	t_ast		*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	return (node);
}

void	free_ast(t_ast *node)
{
	int				i;

	i = 0;
	if (!node)
		return ;
	if (node->type == WORD && node->args)
	{
		while (node->args && node->args[i])
		{
			free(node->args[i]);
			i++;
		}
		free(node->args);
	}
	//free_ast(node->left);
	//free_ast(node->right);
	//free(node);
}

t_ast	*create_and_link_redirection(t_token **tokens, t_token *tmp)
{
	t_ast	*redirect_node;

	redirect_node = new_ast_node((*tokens)->type);
	*tokens = (*tokens)->next->next;
	redirect_node->left = parse_redirection(tokens);
	redirect_node->right = create_file_node(tmp->next);
	//free(tmp->value);
	//free(tmp);
	return (redirect_node);
}

int	count_command_arguments(t_token *current)
{
	int	arg_count;

	arg_count = 0;
	while (current && current->type == WORD)
	{
		arg_count++;
		current = current->next;
	}
	return (arg_count);
}

void	fill_command_arguments(t_ast *command_node,
	t_token **tokens, int arg_count)
{
	int		i;
	t_token	*tmp;

	i = 0;
	memset(&tmp, 0, sizeof(t_token));
	while (i < arg_count)
	{
		command_node->args[i] = ft_strdup((*tokens)->value);
		tmp = *tokens;
		*tokens = (*tokens)->next;
		//free(tmp->value);
		//free(tmp);
		i++;
	}
	command_node->args[arg_count] = NULL;
}