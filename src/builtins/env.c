#include "../../include/minishell.h"

void    env(t_env *env_list)
{
    t_env   *current;

    current = env_list;
    while (current)
    {
        printf("%s\n", current->line);
        current = current->next;
    }
}