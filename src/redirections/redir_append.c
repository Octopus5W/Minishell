#include "../../include/minishell.h"

int	redir_out(t_data *data, char **cmd, char *file)
{
    int pid;
	int file_fd;
    int status;

    (void)data;
    file_fd = 0;
    pid = fork();
    if (pid == 0)
    {
        file_fd = open(file, O_CREAT | O_WRONLY, 0777);
        dup2(file_fd, STDOUT_FILENO);
        echo(cmd);
        //execution_cmd(data, cmd);
    }
    waitpid(pid, &status, 0);
    close(file_fd);
    return (0);
}