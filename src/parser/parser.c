#include "../../include/minishell.h"

t_ast	*parse_command(t_token **tokens)
{
	t_ast	*command_node;
	int		arg_count;

	command_node = new_ast_node(WORD);
	arg_count = count_command_arguments(*tokens);
	command_node->args = ft_calloc(arg_count + 1, sizeof(char *));
	if (!command_node->args)
		return (NULL);
	fill_command_arguments(command_node, tokens, arg_count);
	return (command_node);
}

t_ast	*create_file_node(t_token *token)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = token->type;
	node->args = ft_calloc(2, sizeof(char *));
	if (!node->args)
	{
		//free(node);
		return (NULL);
	}
	if (token->value)
		node->args[0] = ft_strdup(token->value);
	//free(token);
	return (node);
}

t_ast	*parse_redirection(t_token **tokens)
{
	t_token	*tmp;
	t_ast	*redirect_node;
	t_token	*next_token;

	if (!*tokens)
		return (NULL);
	tmp = *tokens;
	if ((*tokens)->type >= IN && (*tokens)->type <= HEREDOC)
		return (create_and_link_redirection(tokens, tmp));
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if ((*tokens)->next->type >= IN && (*tokens)->next->type <= HEREDOC)
		{
			redirect_node = new_ast_node((*tokens)->next->type);
			(*tokens)->next = next_token->next->next;
			redirect_node->left = parse_redirection(&tmp);
			redirect_node->right = create_file_node((next_token->next));
			return (/*free(next_token->value), free(next_token),*/ redirect_node);
		}
		*tokens = next_token;
	}
	return (parse_command(&tmp));
}

t_ast	*parse_pipeline(t_token **tokens)
{
	t_token	*tmp;
	t_token	*next_token;
	t_ast	*pipe_node;

	tmp = *tokens;
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if ((*tokens)->next->type == PIPE)
		{
			pipe_node = new_ast_node((*tokens)->next->type);
			(*tokens)->next = NULL;
			pipe_node->left = parse_redirection(&tmp);
			pipe_node->right = parse_pipeline(&(next_token->next));
			// free(next_token->value);
			// free(next_token);
			return (pipe_node);
		}
		*tokens = next_token;
	}
	return (parse_redirection(&tmp));
}

t_ast	*parse_tokens(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	return (parse_pipeline(tokens));
}

