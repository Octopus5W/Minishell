#include "minishell.h"

static int ft_strslen(char **strs)
{
    int i;

    i = 0;
    while (strs[i])
        i++;
    return (i);
}

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

// ls -l | wc -l > output.txt | ls > output2.txt

// int main()
// {
//     // t_astnode   *node;

//     // node = malloc(sizeof(t_astnode));
//     // node->left = NULL;
//     // node->right = NULL;
//     // node->cmd[0] = ft_strdup("echo");
//     char    **cmd;

//     cmd = malloc(sizeof(char *) * 3);
//     memset(cmd, 0, sizeof(char*));
//     cmd[0] = ft_strdup("echo");
//     cmd[1] = ft_strdup("-nnnnnnnnnl");
//     cmd[2] = ft_strdup("hello world");
//     echo(cmd);
// }