#include "../../include/minishell.h"

// Extract the variable name from the env
char	*extract_name(char *str)
{
	char	*name;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = ft_strndup(str, i);
	if (!name)
		return (NULL);
	return (name);
}

// Extract the variable content from the env
char	*extract_var(char *str)
{
	char	*var;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	j = i;
	while (str[j] && str[j] != ' ' && str[j] != '\t')
		j++;
	if ((str[i] == '\'' && str[ft_strlen(str) - 1] == '\'')
		|| (str[i] == '\"' && str[ft_strlen(str) - 1] == '\"'))
		var = ft_substr(str, i + 1, ft_strlen(str) - i - 2);
	else if (str[j] == ' ' || str[j] == '\t')
		var = ft_substr(str, i, ft_strlen(str) - j - 1);
	else
		var = ft_substr(str, i, ft_strlen(str) - i);
	if (!var)
		return (NULL);
	return (var);
}

// Create a node
t_env	*create_node(char *var)
{
	t_env	*new_node;
	char		*tmp;

	tmp = NULL;
	new_node = NULL;
	new_node = ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->name = extract_name(var);
	if (!new_node->name)
		return (free(new_node), NULL);
	new_node->var = extract_var(var);
	if (!new_node->var)
		return (free(new_node->name), free(new_node), NULL);
	tmp = ft_strjoin(new_node->name, "=");
	if (!tmp)
		return (free(new_node->name), free(new_node->var), free(new_node),
			NULL);
	new_node->line = ft_strjoin(tmp, new_node->var);
	if (!new_node->line)
		return (free(tmp), free(new_node->name), free(new_node->var),
			free(new_node), NULL);
	return (free(tmp), new_node);
}

static int	add_node(t_data *data, char *var)
{
	t_env	*new;
	t_env	*tail;

	tail = NULL;
	new = create_node(var);
	if (!new)
		return (1);
	if (!data->env_list)
		data->env_list = new;
	else
	{
		tail = data->env_list;
		while (tail->next)
			tail = tail->next;
		tail->next = new;
		new->prev = tail;
	}
	return (0);
}

// duplicate all environment variables into a linked list
int	duplicate_env(t_data *data, char **env)
{
	int i;

	i = 0;
	data->env_list = NULL;
	while (env[i])
	{
		if (add_node(data, env[i]))
			return (1);
		i++;
	}
	return (0);
}