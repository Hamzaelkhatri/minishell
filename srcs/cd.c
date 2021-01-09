#include "minishell.h"

void cd_cmd(char *nextPath,t_path *path)
{
    char *s;
    char *s1;
    if(nextPath==NULL)
        nextPath = search_env(path->env->fullenv,"HOME");
    edit_env(path->env->fullenv,"OLDPWD",getcwd(NULL,100));
    if(chdir(nextPath)<0)
       ft_putendl_fd(strerror(errno),1);
    edit_env(path->env->fullenv,"PWD",getcwd(NULL,100));
}
