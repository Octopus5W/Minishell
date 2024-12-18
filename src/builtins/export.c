#include "../../include/minishell.h"

static t_env   *last_node(t_env *env_list)
{
    if (!env_list)
        return (NULL);
    while (env_list->next)
        env_list = env_list->next;
    return (env_list);
}

int	check_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if ((str[i] >= 'A' && str[i] <= 'Z') || ft_isdigit(str[i])
			|| str[i] == '_')
			i++;
		else
			return (1);
	}
	if (!str[i])
		return (1);
	i++;
	return (0);
}

void	append_node(t_env **env_list, t_env *new)
{
	t_env	*last;

	if (!env_list || !new)
		return ;
	if (!(*env_list))
	{
		*env_list = new;
		return ;
	}
	last = last_node(*env_list);
	if (last)
	{
		last->next = new;
		new->prev = last;
	}
}

int	add_env(t_data *data, char *var)
{
	t_env	*new;

	new = create_node(var);
	if (!new)
		return (1);
	append_node(&data->env_list, new);
	return (0);
}

int	export(t_data *data, char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (!check_str(cmd[i]))
			if (add_env(data, cmd[i]))
				return (1);
		i++;
	}
	return (0);
}