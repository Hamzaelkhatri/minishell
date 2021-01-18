#include "minishell.h"

void cd_cmd(char *nextPath,t_path *path)
{
    char *s;
    char *s1;
    if(nextPath == NULL)
        nextPath = search_env(path->env->fullenv,"HOME");
    if(!ft_strncmp(nextPath,"$",1) && get_var_env(path,nextPath))
        nextPath = ft_strdup(get_var_env(path,nextPath));
    edit_env(path->env->fullenv,"OLDPWD",getcwd(NULL,100));
        // puts(nextPath);
    if(strchr(nextPath,'\n'))
            nextPath=ft_strtrim(nextPath,"\n");
        // exit(0);
    chdir(nextPath);
        // perror("bash");
    edit_env(path->env->fullenv,"PWD",getcwd(NULL,100));
    // show_env(path->env->fullenv);
    // puts(getcwd(NULL,100));
}
