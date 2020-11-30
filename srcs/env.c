#include "../includes/minishell.h"

int ft_strlen(char *str)
{
    int i;
    
    i = 0;
    while (str[i]!= '\0')
    {
        i++;
    }
    return i;
}

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