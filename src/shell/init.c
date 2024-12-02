#include "../../include/minishell.h"

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


int init(t_data *data, char **env)
{
    if (env_list(data, env))
        return (1);
    if (env_array(data, env))
        return (free_list(data), 1);
    return (0);
}
