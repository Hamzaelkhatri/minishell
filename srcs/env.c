#include "minishell.h"

void edit_env(char **env,char *var,char *res)
{
    int i;
    int j;
    int k;

    i = 0;
    k = 0;
    if(search_env(env,var))
        while (env[i])
        {
            if(ft_str_to_equal(env[i],var,ft_strlen(var)))
            {   
                k = 0;
                j =cout_to_char(env[i],'=')+1;
                res = ft_strjoin("=",res);
                env[i] = ft_strjoin(var,res);
            }
            i++;
        }
}

void show_env(char **env)
{
    int i;

    if (!env)
        return;
    i = 0;
    while (env[i])
    {
        ft_putendl_fd(env[i],1);
        i++;
    }
}
