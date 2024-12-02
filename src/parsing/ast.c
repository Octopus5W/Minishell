#include "../../include/minishell.h"

t_ast_node  *new_node(t_type type, char *value)
{
    t_ast_node    *new;

    new = malloc(sizeof(t_ast_node));
    if (!new)
        return (NULL);
    new->type = type;
    new->value = value;
    return (new);
}

int build_ast(t_token *tokens)
{
    t_ast_node  *root;
    int         nbr_pipe;

    root = NULL;
    nbr_pipe = 0;
    // Check if there is a pipe
    while (tokens)
    {
        if (tokens->type == 1)
        {
            root = new_node(PIPE, tokens->value);
            nbr_pipe++;
            break ;
        }
        tokens = tokens->next;
    }
    printf("%s\n", root->value);
    // Return to the start of the list
    while (tokens->prev)
        tokens = tokens->prev;
    // Check if there is other pipe
    while (tokens->type != PIPE)
        tokens = tokens->next;
    tokens = tokens->next;
    while (tokens)
    {
        if (tokens->type == PIPE)
        {
            root->right = new_node(PIPE, tokens->value);
            root = root->right;
            nbr_pipe++;
        }
        tokens = tokens->next;
    }
    while (tokens->prev)
        tokens = tokens->prev;
    while (tokens)
    {
        if (tokens->type == OUT)
        {
            root->right = new_node(PIPE, tokens->value);
            root = root->right;
            nbr_pipe++;
        }
        tokens = tokens->next;
    }
    return (0);
}

// date | wc -c >file"