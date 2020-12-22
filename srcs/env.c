#include "minishell.h"

void show_env(char **env)
{
    int i;

    if (!env)
        return;
    i = 0;
    while (env[i])
    {
        write(1, env[i], ft_strlen(env[i]));
        write(1, "\n", 2);
        i++;
    }
}
