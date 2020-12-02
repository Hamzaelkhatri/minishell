
#include "minishell.h"

void exeute(char **env)
{
    int     a;

    a = fork();
    if(!a)
    {
        char *cmd_args[] = { "ls", "", ""};
        execve("/bin/ls",cmd_args,NULL);
    }
}