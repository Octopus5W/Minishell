#include "../../include/minishell.h"

char	*find_var(t_data *data, char *str)
{
	char	*var;
	int		i;

	i = 0;
	var = NULL;
	while (data->envdup[i])
	{
		if (!ft_strncmp(str + 1, data->envdup[i], ft_strlen(str + 1)))
			var = ft_substr(data->envdup[i], ft_strlen(str),
					ft_strlen(data->envdup[i]) - ft_strlen(str));
		i++;
	}
	return (var);
}

char	*expand_envar(t_data *data, char *expand)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_split(expand, ' ');
	if (!tmp)
		return (NULL);
	if (ft_strslen(tmp) > 1)
	{
		while (tmp[i])
		{
			if (tmp[i][0] == '$')
			{
				expand = find_var(data, tmp[i]);
				break ;
			}
			i++;
		}
	}
	return (expand);
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

