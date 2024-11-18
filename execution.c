#include "minishell.h"

static char    *split_path(char *path, char **s)
{
    char    **strs;
    char    *tpath;
    int     i;

    i = 0;
    strs = ft_split(path, ':');
    while (strs[i])
    {
        tpath = ft_strjoin(strs[i], "/");
        tpath = ft_strjoin(tpath, *s);
        if (!access(tpath, X_OK))
        {
            execve(tpath, s, NULL);
            break ;
        }
        i++;
    }
    printf("%s\n", strerror(i));
    i = -1;
    // while (++i < 10000000)
    //     printf("%s\n", strerror(i));
    return (tpath);
}

void    cmd(char **env, char **s)
{
    char    *path;
    int i;

    i = 0;
    path = NULL;
    while (env[i])
    {
        if (!ft_strncmp(env[i], "PATH=", 5))
        {
            path = &env[i][5];
            break ;
        }
        i++;
    }
    path = split_path(path, s);
}

int main(int argc, char *argv[], char **env)
{
    char    *s[] = {"ecrho", "-menfou", "hello", NULL};

    (void)argc;
    (void)argv;
    cmd(env, s);
}

// echo bonjour ; ls | sort ; echo hey