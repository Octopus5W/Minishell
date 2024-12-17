#include "../../include/minishell.h"

static int    option(char  **cmd)
{
    int i;

    i = 2;
    if (ft_strslen(cmd) == 2)
        return (0);
    else
    {
        while (cmd[i])
        {
            printf("%s", cmd[i]);
            i++;
        }
    }
    return (0);
}

int    echo(char **cmd)
{
    int i;

    i = 1;
    if (ft_strslen(cmd) == 1)
        return (printf("\n"), 0);
    if (ft_strcmp(cmd[1], "-n"))
        if (!option(cmd))
            return (1);
    while (cmd[i])
    {
        printf("%s", cmd[i]);
        if (i != ft_strslen(cmd) - 1)
            printf(" ");
        i++;
    }
    printf("\n");
    return (0);
}
