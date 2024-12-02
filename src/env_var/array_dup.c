#include "../../include/minishell.h"

// duplicate all environment variables into an array
int env_array(t_data *data, char **env)
{
    int i;
    int len;

    i = 0;
    len = ft_strslen(env);
    data->env_array = ft_calloc(sizeof(char *), len + 1);
    if (!data->env_array)
        return (1);
    while (env[i])
    {
        data->env_array[i] = ft_strdup(env[i]);
        if (!data->env_array[i])
            return (free_array(data->env_array, i), 1);
        i++;
    }
    return (0);
}