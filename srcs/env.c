#include "../includes/minishell.h"

void show_env(char **env)
{
    int i;
    if (!env)
        return;
    i = 0;
    while (env[i])
    {
        write(1, env[i], ft_strlen(env[i]));
        int c = '\n';
        write(1, &c, 1);
        i++;
    }
}

