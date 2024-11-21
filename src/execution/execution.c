#include "../../include/minishell.h"

// Free the array in case of malloc error
static void	free_array(char **strs, int i)
{
	int	j;

	j = 0;
	while (i)
	{
		free(strs[j]);
		i--;
		j++;
	}
	free(strs);
}

int	actual_exec(char *path, char *cmd)
{
	pid_t	pid;
	int		status;
	char	**split_cmd;

	split_cmd = ft_split(cmd, ' ');
	if (!split_cmd)
		return (1);
	pid = fork();
	if (pid < 0)
	{
		perror("Fork failed\n");
		free_array(split_cmd, ft_strslen(split_cmd) - 1);
		exit(1);
	}
	else if (pid == 0)
	{
		if (execve(path, split_cmd, NULL))
		{
			perror("exex failed\n");
			exit(1);
		}
	}
	else
		waitpid(pid, &status, 0);
	free_array(split_cmd, ft_strslen(split_cmd) - 1);
	return (0);
}

/* Exctract and concatene the line path to use it */
int	split_path(char *path, t_data *data)
{
	char	**strs;
	char	*tmp;
	int		i;

	i = 0;
	strs = ft_split(path, ':');
	if (!strs)
		return (1);
	while (strs[i])
	{
		path = ft_strjoin(strs[i], "/");
		if (!path)
			return (free_array(strs, i), 1);
		tmp = path;
		// free(path);
		// path = NULL;
		path = ft_strjoin(tmp, data->node->cmd);
		if (!path)
			return (free(tmp), free_array(strs, i), 1);
		if (access(path, X_OK) == 0)
			actual_exec(path, data->node->cmd);
		// free(path);
		// path = NULL;
		i++;
	}
	free_array(strs, ft_strslen(strs) - 1);
	return (free(tmp), free(path), 0);
}

/* Find the line path in env */
int	find_path(t_data *data)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (data->env_array[i])
	{
		if (!ft_strncmp(data->env_array[i], "PATH=", 5))
		{
			path = &data->env_array[i][5];
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
	if (data->node->isbuiltin)
		return (0); // builtins(); TO DO
	else
		find_path(data);
	return (0);
}
