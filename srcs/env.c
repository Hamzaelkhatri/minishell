#include "../includes/minishell.h"

void show_env(char **env)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (env[i] != '\0')
    {
        j = 0;
        write(1,env[i],ft_strlen(env[i]));
        write(1,"\n",2);
        i++;
    }
}