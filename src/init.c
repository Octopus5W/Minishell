#include "../include/minishell.h"

/* Check if the cmd in the node is a builtin */
// int check_builtins(t_data *data)
// {
//     if (!ft_strncmp(data->node->cmd, "echo", 4))
//         data->node->isbuiltin = true;
//     else if (!ft_strncmp(data->node->cmd, "cd", 2))
//         data->node->isbuiltin = true;
//     else if (!ft_strncmp(data->node->cmd, "pwd", 3))
//         data->node->isbuiltin = true;
//     // else if (!ft_strncmp(data->node->cmd[0], "env", 3))
//     //     data->isbuiltin = true;
//     return (0);
// }

void    free_envdup(t_data *data, int i)
{
    while (--i)
        free(data->env_array[i]);
    free(data->env_array);
}

int env_array(t_data *data, char **env)
{
    int i;
    int len;

    i = 0;
    len = ft_strslen(env);
    data->env_array = malloc(sizeof(char *) * len + 1);
    if (!data->env_array)
        return (1);
    while (env[i])
    {
        data->env_array[i] = ft_strdup(env[i]);
        if (!data->env_array[i])
            return (free_envdup(data, i), 1);
        i++;
    }
    return (0);
}

static void free_list(t_data *data)
{
    t_list  *next;

    next = NULL;
    while (data->env_list)
    {
        next = data->env_list->next;
        free(data->env_list);
        data->env_list = next;
    }
}

// duplicate the env variables in a linked list
static int env_list(t_data *data, char **env)
{
    int i;

    i = 0;
    data->env_list = ft_lstnew((char *)env[i++]);
    if (!data->env_list)
        return (1);
    while (env[i])
    {
        data->env_list->next = ft_lstnew((char *)env[i]);
        if (!data->env_list->next)
            return (free_list(data), 1);
        data->env_list = data->env_list->next;
        i++;
    }
    return (0);
}

int init(t_data *data, char **env)
{
    //check_builtins(data);
    if (env_list(data, env))
        return (1);
    if (env_array(data, env))
        return (1);
    return (0);
}