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
	t_env *next;

	next = NULL;
	while (data->env_list)
	{
		next = data->env_list->next;
		free(data->env_list->name);
		free(data->env_list->var);
		free(data->env_list->line);
		free(data->env_list);
		data->env_list = next;
	}
}

// static int	actual_exec(char *path, char **cmd)
// {
// 	pid_t	pid;
// 	int		status;

// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		perror("Fork failed\n");
// 		exit(1);
// 	}
// 	else if (pid == 0)
// 	{
// 		if (execve(path, cmd, NULL))
// 		{
// 			perror("exex failed\n");
// 			exit(1);
// 		}
// 	}
// 	else
// 		waitpid(pid, &status, 0);
// 	return (0);
// }

// static int	check(char *str, char **cmd)
// {
// 	char	*path;
// 	char	*tmp;

// 	path = ft_strjoin(str, "/");
// 	if (!path)
// 		return (0);
// 	tmp = path;
// 	path = ft_strjoin(tmp, cmd[0]);
// 	if (!path)
// 		return (free(tmp), 0);
// 	if (!access(path, X_OK))
// 	{
// 		actual_exec(path, cmd);
// 		return (free(tmp), free(path), 1);
// 	}
// 	free(path);
// 	free(tmp);
// 	return (0);
// }

// /* Exctract and concatene the line path to use it */
// static int	split_path(char *path, char **cmd)
// {
// 	char	**strs;
// 	int		i;

// 	i = 0;
// 	strs = ft_split(path, ':');
// 	if (!strs)
// 		return (1);
// 	while (strs[i])
// 	{
// 		if (check(strs[i], cmd))
// 			break ;
// 		i++;
// 	}
// 	free_array(strs, ft_strslen(strs));
// 	return (0);
// }

// static int	find_path(t_data *data, char **cmd)
// {
// 	t_env	*current;

// 	current = data->env_list;
// 	while (current)
// 	{
// 		if (!ft_strncmp("PATH", current->name, 5))
// 		{
// 			if (split_path(current->var, cmd))
// 				return (1);
// 			break ;
// 		}
// 		current = current->next;
// 	}
// 	return (0);
// }

static int	actual_exec(char *path, char **cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("Fork failed\n");
		exit(1);
	}
	else if (pid == 0)
	{
		if (execve(path, cmd, NULL))
		{
			perror("exex failed\n");
			exit(1);
		}
	}
	else
		waitpid(pid, &status, 0);
	return (0);
}

static int	check(char *str, char **cmd)
{
	char	*path;
	char	*tmp;

	path = ft_strjoin(str, "/");
	if (!path)
		return (0);
	tmp = path;
	path = ft_strjoin(tmp, cmd[0]);
	if (!path)
		return (free(tmp), 0);
	if (!access(path, X_OK))
	{
		actual_exec(path, cmd);
		return (free(tmp), free(path), 1);
	}
	free(path);
	free(tmp);
	return (0);
}

/* Exctract and concatene the line path to use it */
static int	split_path(char *path, char **cmd)
{
	char	**strs;
	int		i;

	i = 0;
	strs = ft_split(path, ':');
	if (!strs)
		return (1);
	while (strs[i])
	{
		if (check(strs[i], cmd))
			break ;
		i++;
	}
	free_array(strs, ft_strslen(strs));
	return (0);
}

static int	external_command(t_data *data, char **cmd)
{
	t_env	*current;

	current = data->env_list;
	while (current)
	{
		if (!ft_strncmp("PATH", current->name, 5))
		{
			if (split_path(current->var, cmd))
				return (1);
			break ;
		}
		current = current->next;
	}
	return (0);
}

int	command(t_data *data, char **cmd)
{
	if (ft_strcmp(cmd[0], "echo"))
	{
		if (echo(cmd))
			return (1);
	}
	else if (ft_strcmp(cmd[0], "pwd"))
	{
		if (pwd())
			return (1);
	}
	else if (ft_strcmp(cmd[0], "env"))
		env(data->env_list);
	else if (ft_strcmp(cmd[0], "export"))
	{
		if (export(data, cmd))
			return (1);
	}
	else if (ft_strcmp(cmd[0], "unset"))
	{
		if (unset(data, cmd))
			return (1);
	}
	else if (ft_strcmp(cmd[0], "cd"))
	{
		if (cd(cmd))
			return (1);
	}
	else 
		if (external_command(data, cmd))
			return (1);
	return (0);
}

