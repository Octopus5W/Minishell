#include "../include/minishell.h"

/* Check if the cmd in the node is a builtin */
int check_builtins(t_data *data)
{
    if (!ft_strncmp(data->node->cmd[0], "echo", 4))
        data->isbuiltin = true;
    else if (!ft_strncmp(data->node->cmd[0], "cd", 2))
        data->isbuiltin = true;
    else if (!ft_strncmp(data->node->cmd[0], "pwd", 3))
        data->isbuiltin = true;
    // else if (!ft_strncmp(data->node->cmd[0], "env", 3))
    //     data->isbuiltin = true;
    return (0);
}

void    free_envdup(t_data *data, int i)
{
    while (--i)
        free(data->envdup[i]);
    free(data->envdup);
}

int duplicate_env(t_data *data, char **env)
{
    int i;
    int len;

    i = 0;
    len = ft_strslen(env);
    data->envdup = malloc(sizeof(char *) * len + 1);
    if (!data->envdup)
        return (1);
    while (env[i])
    {
        data->envdup[i] = ft_strdup(env[i]);
        if (!data->envdup[i])
            return (free_envdup(data, i), 1);
        i++;
    }
    return (0);
}

int init(t_data *data, char **env)
{
    fake_parser(data);
    check_builtins(data);
    if (duplicate_env(data, env))
        return (1);
    return (0);
}