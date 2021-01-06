#include "minishell.h"

void cd_cmd(char *nextPath,t_path *path)
{
    char *s;
    if(!nextPath)
        nextPath = search_env(path->env->fullenv,"HOME");
    getcwd(s,100);
    edit_env(path->env->fullenv,"OLDPWD",s);
    if(chdir(nextPath))
       perror("bash$ ");
    getcwd(s,100);
    edit_env(path->env->fullenv,"PWD",s);
}
