#include "minishell.h"

int main(int argc, char *argv[], char **env)
{
    char    *s1[] = {"who", NULL};
    char    *s2[] = {"who", NULL};
    int     fd[2];
    pid_t   pid1;
    pid_t   pid2;
    (void)argc;
    (void)argv;
    (void)s2;
    if (pipe(fd) == -1)
        return (1);
    pid1 = fork();
    if (pid1 < 0)
        return (1);
    if (pid1 == 0)
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        cmd(env, s1);
    }
    pid2 = fork();
    if (pid2 < 0)
        return (1);
    if (pid2 == 0)
    {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        cmd(env, s2);
    }
    close(fd[0]);
    close(fd[1]);
    return (0);
}