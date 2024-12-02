#include "../../include/minishell.h"

// int main(int argc, char *argv[], char **env)
// {
//     char    *s1[] = {"env", NULL};
//     char    *s2[] = {"wc", "-l", NULL};
//     int     fd[2];
//     pid_t   pid1;
//     pid_t   pid2;
//     (void)argc;
//     (void)argv;
//     (void)s2;
//     if (pipe(fd) == -1)
//         return (1);
//     pid1 = fork();
//     if (pid1 < 0)
//         return (1);
//     if (pid1 == 0)
//     {
//         dup2(fd[1], STDOUT_FILENO);
//         close(fd[0]);
//         close(fd[1]);
//         cmd(env, s1);
//     }
//     pid2 = fork();
//     if (pid2 < 0)
//         return (1);
//     if (pid2 == 0)
//     {
//         dup2(fd[0], STDIN_FILENO);
//         close(fd[0]);
//         close(fd[1]);
//         cmd(env, s2);
//     }
//     close(fd[0]);
//     close(fd[1]);
//     return (0);
// }

// int	set_pipe(int *fd, int end)
// {
// 	if (dup2(fd[end], end) == -1)
// 		return (1);
// 	if (close(fd[0]) == -1)
// 		return (1);
// 	if (close(fd[1]))
// 		return (1);
//     return (0);
// }

// int	pipe_loop(t_data *data, char **cmd)
// {
//     int fd[2];
// 	int pid;
// 	int status;

// 	if (pipe(fd) == -1)
// 		return (1);
// 	pid = fork();
// 	if (pid == -1)
// 		return (1);
// 	else if (pid == 0)
// 	{
// 		if (set_pipe(fd, 1))
// 			return (1);
// 		execution_cmd(data, cmd);
// 	}
// 	waitpid(pid, &status, 0);
// 	set_pipe(fd, 0);
//     return (0);
// }
int	sh_pipe(t_data *data, char ***c)
{
	int i;

	i = 0;
	while (c[i])
	{
		pipe_loop(data, c[i]);
		i++;
	}
	return (0);
}