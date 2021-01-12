#include "minishell.h"

void cd_cmd(char *nextPath,t_path *path)
{
    char *s;
    char *s1;
    if(nextPath==NULL)
        nextPath = search_env(path->env->fullenv,"HOME");
    else if(!ft_strncmp(nextPath,"$",1))
        nextPath = ft_strdup(get_var_env(path,nextPath));
    edit_env(path->env->fullenv,"OLDPWD",getcwd(NULL,100));
    chdir(nextPath);
       ft_putendl_fd(strerror(errno),1);
    edit_env(path->env->fullenv,"PWD",getcwd(NULL,100));
}
