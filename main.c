#include "minishell.h"

int main(int argc, char *argv[], char **env)
{
    t_data  data;
    char    *line;

    (void)argc;
    (void)argv;
    memset(&data, 0, sizeof(t_data));
    while (1)
    {
        line = readline("bash $  ");
        if (ft_strcmp(line, "exit"))
            break ;
        if (init(&data, env)) 
            break ;
        // if (execution_cmd(&data))
        //     break ;
        add_history(line);
        free(line);
    }
    return (0);
}
