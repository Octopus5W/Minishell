#include "../../include/minishell.h"

t_ast	*new_ast_node(t_type type)
{
	t_ast		*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->command = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

// void	free_ast(t_ast *node)
// {
// 	int				i;

// 	i = 0;
// 	if (!node)
// 		return ;
// 	if (node->type == WORD && node->command)
// 	{
// 		while (node->command && node->command[i])
// 		{
// 			free(node->command[i]);
// 			i++;
// 		}
// 		free(node->command);
// 	}
// 	free_ast(node->left);
// 	free_ast(node->right);
// 	free(node);
// }

t_ast	*create_and_link_redirection(t_token **tokens, t_token *tmp)
{
	t_ast	*redirect_node;

	redirect_node = new_ast_node((*tokens)->type);
	*tokens = (*tokens)->next->next;
	redirect_node->left = parse_redirection(tokens);
	redirect_node->right = create_file_node(tmp->next);
	//free(tmp->lexeme);
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

// void	fill_command_arguments(t_ast *command_node,
// 	t_token **tokens, int arg_count)
// {
// 	int		i;
// 	t_token	*tmp;

// 	i = 0;
// 	while (i < arg_count)
// 	{
// 		command_node->command[i] = ft_strdup((*tokens)->lexeme);
// 		tmp = *tokens;
// 		*tokens = (*tokens)->next;
// 		free(tmp->lexeme);
// 		free(tmp);
// 		i++;
// 	}
// 	command_node->command[arg_count] = NULL;
// }

void	fill_command_arguments(t_ast *command_node, t_token **tokens, int arg_count)
{
    int		i;
    //t_token	*tmp;

    i = 0;
    while (i < arg_count)
    {
        command_node->command[i] = ft_strdup((*tokens)->lexeme);
        //tmp = *tokens;
        *tokens = (*tokens)->next;
        //free(tmp);
        i++;
    }
    command_node->command[arg_count] = NULL;
}

void	print_ast(t_ast *node, int depth)
{
    int i;

    if (!node)
        return;

    for (i = 0; i < depth; i++)
        printf("  ");
    printf("Node type: %s\n", get_token_type_name(node->type));

    if (node->command)
    {
        for (i = 0; node->command[i]; i++)
        {
            for (int j = 0; j < depth; j++)
                printf("  ");
            printf("Command: %s\n", node->command[i]);
        }
    }

    print_ast(node->left, depth + 1);
    print_ast(node->right, depth + 1);
}