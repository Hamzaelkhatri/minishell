#include "minishell.h"

void cd_cmd(char *nextPath,t_path *path)
{
    char *s;
    if(!nextPath)
        nextPath = "~";
    getcwd(s,100);
    edit_env(path->env->fullenv,"OLDPWD",s);
    if(chdir(nextPath))
       perror("bash$ ");
    getcwd(s,100);
    edit_env(path->env->fullenv,"PWD",s);
    exit(0);
}
