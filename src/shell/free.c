#include "../../include/minishell.h"

void	free_array(char **strs, int i)
{
	int	j;

	j = 0;
	while (i >= 0)
	{
		free(strs[j]);
		i--;
		j++;
	}
	free(strs);
}

void	free_list(t_data *data)
{
	t_envlist *next;

	next = NULL;
	while (data->env_list)
	{
		next = data->env_list->next;
		free(data->env_list->name);
		free(data->env_list->var);
		free(data->env_list->raw);
		free(data->env_list);
		data->env_list = next;
	}
}
