#include "../../include/minishell.h"

void builtins(t_data *data)
{
    if (ft_strcmp(data->node->cmd[0], "echo"))
        echo(data->node->cmd);
}