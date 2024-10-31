#include "minishell.h"

int main(int argc, char *argv[], char **env)
{
    char    **strs;
    char    *full_path;
    char    *cmd_path;
    char    *cmd_path_2;

    t_cmd   cmd;
    int i;

    i = 0;
    (void)argc;
    (void)argv;
    cmd.cmd = "ls";
    while(env[i])
    {
        if(ft_strncmp(env[i],"PATH",4) == 0)
        {
            full_path = &env[i][5];
            //fprintf(stderr,"%s\n\n",full_path);
            break;
        }
        i++;
    }
    strs = ft_split(full_path, ':');
    // for (int i = 0; strs[i]; i++)
    //     printf("%s\n", strs[i]);
    //printf("\n\n");
    i = 0;
    while(strs[i])
    {
        cmd_path = ft_strjoin(strs[i],"/");
        cmd_path_2 = ft_strjoin(cmd_path, "ls");
        if(!access(cmd_path_2,X_OK))
        {
            execve(cmd_path_2,NULL,env);
            printf("ACCESS OK");
            break;
        }        
        else
        {     
            printf("BAD PATH \n");
            i++;
            continue;
        }
    }
}
