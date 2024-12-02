#include "../../include/minishell.h"

t_envlist   *last_node(t_envlist *env_list)
{
    if (!env_list)
        return (NULL);
    while (env_list->next)
        env_list = env_list->next;
    return (env_list);
}
