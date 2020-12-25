#include "minishell.h"

int ft_strtospace(char *cmd)
{
    int i;
    i = 0;
    while (cmd[i] != ' ')
    {
        i++;
    }
    return i;
}

int check_path(char *path,char *cmd)
{
    int i;
    char **tmp;
    i = 0;
    tmp = ft_split(path,'-');
    while (tmp[i])
    {
        if(ft_strnstr(tmp[i],ft_split(cmd,' ')[0],ft_strtospace(cmd)))
            return i;
        i++;
    }
    return 0;
}

void get_directory(t_path *path)
{
    DIR *dir;
    struct dirent *sd;
    char *tmp;
    char **paths;
    int i = 0;
    
    tmp = search_env(path->env->fullenv,"PATH");
    paths = ft_split(tmp,':');
    while (paths[i])
        i++;
    i =0;
    ft_bzero(tmp,ft_strlen(tmp));
    while (paths[i])
    {
            dir  = opendir(paths[i]);
            if(dir != NULL && !ft_strchr(paths[i],'.'))
            {
                tmp = ft_strjoin(tmp,"+");
                tmp = ft_strjoin(tmp,paths[i]);               
                tmp = ft_strjoin(tmp,"-");
                while ((sd = readdir(dir)) != NULL )
                {
                    tmp = ft_strjoin(tmp,sd->d_name);
                    tmp = ft_strjoin(tmp,"-");
                }
                closedir(dir);
            }
            i++;
    }
    path->cmds= ft_strdup(tmp);
}