#include "minishell.h"

void    expand(char **env, char **cmd)
{
    int i;
    int j;
    char    *var;

    i = 1;
    j = 0;
   
    while (cmd[i])
    {
        if (ft_strncmp(cmd[i][0], "$", 1))
        {
            var = ft_substr(cmd[i], 2, ft_strlen(cmd[i] - 1));
            while (env[j])
            {
                if (!ft_strncmp(env[i], var, ft_strlen(var)))
                {
                    
                }

                j++;
            }
        }
        i++;
    }
}
