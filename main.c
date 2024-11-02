#include "minishell.h"

int main(int argc, char *argv[])
{
    char    *r_line;

    (void)argc;
    (void)argv;
    while (1)
    {
        r_line = readline("$ ");
        if (ft_strcmp(r_line, "exit"))
            break ;
        add_history(r_line);
        free(r_line);
    }
    return (0);
}
