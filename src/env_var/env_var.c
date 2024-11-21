#include "../../include/minishell.h"

char	*env_expand(t_data *data, char *to_expand)
{
	t_list	*current;
	char	*str;
	char	*env;

	current = data->env_list;
	str = ft_substr(to_expand, 1, ft_strlen(to_expand) - 1);
	if (!str)
		return (NULL);
	while (current->next)
	{
		if (!ft_strncmp((char *)current->content, str, ft_strlen(str)))
		{
			env = ft_substr((char *)current->content, ft_strlen(str) + 1,
					ft_strlen((char *)current->content) - ft_strlen(str) - 1);
			if (!env)
				return (NULL);
		}
		current = current->next;
	}
	free(str);
	return (env);
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
