#include "../../include/minishell.h"

int	execution_pipe(t_data *data, t_ast *left, t_ast *right)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

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
		command(data, left->command);
        exit(1);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (1);
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		command(data, right->command);
        exit(1);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

int	execution(t_data *data, t_ast *ast)
{
	t_ast *head;
	t_ast *right;

	head = ast;
	right = head->right;
	if (head->type == PIPE)
	{
		if (execution_pipe(data, head->left, right))
			return (1);
		if (right->type == PIPE)
			execution(data, right);
		// if (head->right->type == PIPE)
		//     execution(data, head->right);
	}
	else
	{
	    command(data, head->command);
	}
	return (0);
}