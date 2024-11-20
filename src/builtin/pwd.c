#include "../../include/minishell.h"

int	pwd(char **cmd)
{
	char	path[1024];

	if (ft_strcmp(cmd[0], "pwd") && getcwd(path, sizeof(path)))
		printf("%s\n", path);
	else
		return (printf("getcwd error\n"), 1);
	return (0);
}

int	main(void)
{
	char **cmd;

	cmd = malloc(sizeof(char *) * 1);
	cmd[0] = ft_strdup("pwd");
	pwd(cmd);
}