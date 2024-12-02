#include "../../include/minishell.h"
void	print_list(t_data *data)
{
	t_envlist	*current;

	current = data->env_list;
	while (current)
	{
		printf("%s\n", current->raw);
		current = current->next;
	}
}
void envv(t_data *data)
{
    print_list(data);
}