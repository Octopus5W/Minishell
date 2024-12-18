#include "../../include/minishell.h"

int	pwd(void)
{
	char	path[1024];

	if (getcwd(path, sizeof(path)))
		printf("%s\n", path);
	else
	{
		printf("getcwd error\n");
		return (1);
	}
	return (0);
}
