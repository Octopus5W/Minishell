#include "minishell.h"

void    fake_parser(t_data *data)
{
	data->node = malloc(sizeof(t_astnode));
	data->node->cmd = malloc(sizeof(char) * 4);
	data->node->cmd[0] = ft_strdup("echo");
	data->node->cmd[1] = ft_strdup("$HOME");
	data->node->cmd[2] = NULL;
	data->isbuiltin = false;
	data->node->left = NULL;
	data->node->right = NULL;
}