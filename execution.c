#include "minishell.h"

/* Exctract and concatene the line path to use it */
int split_path(char *path, t_data *data)
{
	char	**strs;
	int		i;

	i = 0;
	strs = ft_split(path, ':');
	while (strs[i])
	{
		path = ft_strjoin(strs[i], "/");
		path = ft_strjoin(path, *data->node->cmd);
		if (!access(path, X_OK))
			execve(path, data->node->cmd, NULL);
		i++;
	}
	return (0);
}

/* Find the line path in env */
int find_path(t_data *data)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (data->envdup[i])
	{
		if (!ft_strncmp(data->envdup[i], "PATH=", 5))
		{
			path = &data->envdup[i][5];
			break ;
		}
		i++;
	}
	if (split_path(path, data))
        return (1);
	return (0);
}

int	execution_cmd(t_data *data)
{
	if (data->isbuiltin)
		builtins();
    else
        find_path(data);
    return (0);
}
