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
    if (ft_strslen(cmd) > 2)
    {
        printf("cd: too many arguments\n");
        return (1);
    }
	else if (ft_strslen(cmd) == 1)
	{
		no_path(cmd); /* if only cd ---> redir to home */
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
