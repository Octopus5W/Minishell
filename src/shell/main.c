#include "../../include/minishell.h"

// void	print_list(t_data *data)
// {
// 	t_envlist	*current;

// 	current = data->env_list;
// 	while (current)
// 	{
// 		printf("%s\n", current->raw);
// 		// printf("%s	%s\n", current->name, current->var);
// 		current = current->next;
// 	}
// }

void	print_array(t_data *data)
{
	int	i;

	i = 0;
	while (data->env_array[i])
	{
		printf("%s\n", data->env_array[i]);
		i++;
	}
}

// int	main(int argc, char *argv[], char **env)
// {
// 	t_data	data;
// 	char	**cmd;
// 	char	**cmd2;

// 	(void)argc;
// 	(void)argv;
// 	memset(&data, 0, sizeof(t_data));
// 	init(&data, env);
// 	cmd = malloc(3 * sizeof(char *));
// 	cmd[0] = ft_strdup("export");
// 	cmd[1] = ft_strdup("TEST1=hello world");
// 	// cmd[2] = ft_strdup("TESTDEUX=\"hello\"");
// 	cmd[2] = NULL;
// 	cmd2 = malloc(3 * sizeof(char *));
// 	cmd2[0] = ft_strdup("unset");
// 	cmd2[1] = ft_strdup("TEST");
// 	// cmd2[2] = ft_strdup("TESTDEUX");
// 	cmd2[2] = NULL;
// 	export(&data, cmd);
// 	envv(&data);
// 	printf("\n");
// 	unset(&data, cmd2);
// 	envv(&data);
// 	// print_array(&data);
// 	// free_list(&data);
// 	//free_array(&data, ft_strslen(env));
// 	// free(cmd[0]);
// 	// free(cmd[1]);
// 	// free(cmd[2]);
// 	// free(cmd);
// 	// free(cmd2[0]);
// 	// free(cmd2[1]);
// 	// free(cmd2[2]);
// 	// free(cmd2);
// 	return (0);
// }

// //Main EXEC
// int	main(int argc, char **argv, char **env)
// {
// 	t_data	data;
// 	char	**cmd;

// 	(void)argc;
// 	(void)argv;
// 	ft_memset(&data, 0, sizeof(t_data));
// 	init(&data, env);
// 	cmd = malloc(2 * sizeof(char *));
// 	cmd[0] = ft_strdup("who");
// 	// cmd[1] = ft_strdup("Hello World");
// 	cmd[1] = NULL;
// 	execution_cmd(&data, cmd);
// 	free_list(&data);
// 	free_array(data.env_array, ft_strslen(data.env_array));
// 	free(cmd[0]);
// 	free(cmd[1]);
// 	free(cmd);
// 	return (0);
// }

// // Main PIPE
// int	main(int argc, char **argv, char **env)
// {
// 	t_data	data;
// 	char	**cmd;
// 	// char	**cmd1;

// 	(void)argc;
// 	(void)argv;
// 	ft_memset(&data, 0, sizeof(t_data));
// 	init(&data, env);
// 	cmd = malloc(2 * sizeof(char *));
// 	cmd[0] = ft_strdup("who");
// 	cmd[1] = NULL;
// 	// cmd1 = malloc(3 * sizeof(char *));
// 	// cmd1[0] = ft_strdup("wc");
// 	// cmd1[1] = ft_strdup("-l");
// 	// cmd1[2] = NULL;
// 	redir_out(&data, cmd, "file.txt");
// 	return (0);
// }

// int main(int argc, char *argv[], char **env)
// {
// 	t_data	data;
//     char    *s1[] = {"env", NULL};
//     char    *s2[] = {"wc", NULL};
//     int     fd[2];
//     pid_t   pid1;
//     pid_t   pid2;
//     (void)argc;
//     (void)argv;
//     (void)s2;
// 	memset(&data, 0, sizeof(t_data));
// 	init(&data, env);
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
//        execution_cmd(&data, s1);
//     }
//     pid2 = fork();
//     if (pid2 < 0)
//         return (1);
//     if (pid2 == 0)
//     {
//         dup2(fd[0], STDIN_FILENO);
//         close(fd[0]);
//         close(fd[1]);
//         execution_cmd(&data, s2);
//     }
//     close(fd[0]);
//     close(fd[1]);
//     return (0);
// }

void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		printf("%s	%d\n", current->value, current->type);
		// printf("%s	%s\n", current->name, current->var);
		current = current->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	t_token	*tokens;

	tokens = malloc(sizeof(t_token));
	tokens->type = WORD;
	tokens->value = strdup("date");
	tokens->prev = NULL;
	tokens->next = malloc(sizeof(t_token));
	tokens->next->type = PIPE;
	tokens->next->value = strdup("|");
	tokens->next->prev = tokens;
	tokens->next->next = malloc(sizeof(t_token));
	tokens->next->next->type = WORD;
	tokens->next->next->value = strdup("wc -c");
	tokens->next->next->prev = tokens->next;
	tokens->next->next->next = malloc(sizeof(t_token));
	tokens->next->next->next->type = OUT;
	tokens->next->next->next->value = strdup(">");
	tokens->next->next->next->prev = tokens->next->next;
	tokens->next->next->next->next = malloc(sizeof(t_token));
	tokens->next->next->next->next->type = WORD;
	tokens->next->next->next->next->value = strdup("file");
	tokens->next->next->next->next->prev = tokens->next->next->next;
	
	print_tokens(tokens);
	printf("\n");
	build_ast(tokens);
}

// date | wc -c >file"