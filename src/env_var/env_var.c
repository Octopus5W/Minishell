#include "../../include/minishell.h"

char	*env_expand(t_data *data, char *to_expand)
{
	t_envlist	*current;
	char		*var_name;

	current = data->env_list;
	var_name = ft_substr(to_expand, 1, ft_strlen(to_expand) - 1);
	if (!var_name)
		return (NULL);
	while (current->next)
	{
		if (!ft_strncmp(current->name, var_name, ft_strlen(var_name)))
			return (free(var_name), current->var);
		current = current->next;
	}
	free(var_name);
	return (NULL);
}

// int	main(int ac, char **av, char **env)
// {
// 	t_data	data;
// 	char	*var;

// 	(void)ac;
// 	(void)av;
// 	var = NULL;
// 	memset(&data, 0, sizeof(t_data));
// 	if (init(&data, env))
// 		return (1);
// 	data.str = ft_strdup("echo $HOME");
// 	var = expand_envar(&data, var);
// }
