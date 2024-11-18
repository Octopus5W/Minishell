#include "minishell.h"

int	envv(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	envv(env);
}