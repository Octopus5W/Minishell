#include "../../include/minishell.h"

static int	find_var(t_data *data, char *cmd)
{
	t_env	*current;

	current = data->env_list;
	while (current)
	{
		if (!ft_strncmp(cmd, current->name, ft_strlen(cmd)))
		{
			if (current->prev)
				current->prev->next = current->next;
			if (current->next)
				current->next->prev = current->prev;
			if (current == data->env_list)
			{
				data->env_list = current->next;
				data->env_list->prev = NULL;
			}
			free(current->name);
			free(current->var);
			free(current->line);
			free(current);
			return (0);
		}
		current = current->next;
	}
	return (1);
}

int	unset(t_data *data, char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (find_var(data, cmd[i]))
			return (1);
		i++;
	}
	return (0);
}