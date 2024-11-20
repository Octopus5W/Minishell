#include "../include/minishell.h"

int main(int argc, char *argv[], char **env)
{
    t_data  data;
    char    *line;

    (void)argc;
    (void)argv;
    memset(&data, 0, sizeof(t_data));
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
