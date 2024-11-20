#include "../include/minishell.h"

// int main ()
// {
// 	t_token* tokens/*, *tokensdeux*/;
// 	char *s = "echo -n >lol | echo <lol -n <mdr";
// 	int i = 0;

// 	if (!quote_is_closed(s))
// 		return (0);
// 	tokens = tokenaizer(s);
// 	// tokensdeux = tokens->next;
// 	while (tokens)
// 	{
// 		i++;
// 		printf("Token %d:\ntype: %i\nvalue: %s\nnext: %p\n----------------------------------\n", i, tokens->type, tokens->value, tokens->next);
// 		if (i%2 == 0)
// 		{
// 			tokens = token_delete(tokens);
// 		}
// 		else
// 			tokens = tokens->next;
// 	}
// 	i=0;
// 	// printf("\n\n\n");
// 	// while (tokensdeux)
// 	// {
// 	// 	i++;
// 	// 	printf("Token %d:\ntype: %i\nvalue: %s\nnext: %p\n----------------------------------\n", i, tokens->type, tokens->value, tokens->next);
// 	// 	tokensdeux = tokensdeux->next;
// 	// }
// }

int main(int argc, char *argv[], char **env)
{
    t_data  data;
    char    *line;

    (void)argc;
    (void)argv;
    memset(&data, 0, sizeof(t_data));
    data.node = malloc(sizeof(t_ast)); // a supprimer
    data.node->cmd = ft_strdup("ls"); // a supprimer
    data.node->left = NULL;
    data.node->right = NULL;
    while (1)
    {
        line = readline("$  ");
        if (init(&data, env)) 
            return (1);
        if (execution_cmd(&data))
            return (1);
        add_history(line);
        free(line);
    }
    return (0);
}
