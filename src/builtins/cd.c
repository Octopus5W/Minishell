#include "../../include/minishell.h"

void	no_path(char **cmd)
{
	if (!opendir(cmd[1]))
	{
		perror("opendir failed");
		exit(1);
	}
	if (!chdir("$HOME"))
	{
		perror("chdir failed");
		exit(1);
	}
}

int	cd(char **cmd)
{
	int	i;

	i = 1;
	if (ft_strslen(cmd) == 1)
	{
		// if only cd ---> redir to home
		no_path(cmd);
		return (0);
	}
	else
	{
		if (chdir(cmd[1]) == -1)
		{
			perror("chdir() error");
			return (1);
		}
	}
	return (0);
}

// int	main(void)
// {
// 	char **cmd;

// 	cmd = malloc(sizeof(char *) * 1);
// 	memset(cmd, 0, sizeof(char *));
// 	cmd[0] = ft_strdup("cd");
// 	cmd[1] = ft_strdup("test/");
// 	cd(cmd);
// }