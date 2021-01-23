#include "../includes/minishell.h"

void show_env1(char **env)
{
    int i;
    char **spl;
    if (!env)
        return;
    i = 0;
    while (env[i])
    {
        spl = ft_split(env[i], '=');
        if (ft_strcmp(spl[0], "_"))
        {
            write(1, "declare -x ", 11);
            write(1, env[i], ft_strlen(env[i]));
            int c = '\n';
            write(1, &c, 1);
        }
        free(spl);
        i++;
    }
}

int check_equal(char *env)
{
    int i = 0;
    int j = 0;
    while (env[i] && i != ft_strlen(env))
    {
        if (env[i] == '=')
            return (1);
        i++;
    }
    return (0);
}
void show_env(char **env)
{
    int i;
    if (!env)
        return;
    i = 0;
    int j = 0;
    i = 0;
    while (env[i] && (check_equal(env[i]) == 1))
    {
        write(1, env[i], ft_strlen(env[i]));
        int c = '\n';
        write(1, &c, 1);
        i++;
    }
}