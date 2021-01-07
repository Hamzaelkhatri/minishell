#include "minishell.h"

// void cd_cmd(char *nextPath,t_path *path)
// {
//     char *s;
//     getcwd(path->env->oldpwd,100);
//     if(chdir(nextPath))
//     {
//         perror("bash$ ");
//     }
//     getcwd(s,100);
//     path->env->pwd = ft_strdup(s);
// }
// void cd_cmd(char *nextPath,t_path *path)
// {
//     char *s;

//     // if(
//     // printf("\n {%s} \n",getcwd(path->env->oldpwd,100));
//         // printf("\n +++++++++ \n");
//         // printf("{%s}",nextPath);
//     // printf("\n |%s| \n", nextPath);
//     chdir(nextPath);
//     // chdir(nextPath);
//     // {
//         // perror("bash$ ");
//     // }
//     // getcwd(s,100);
//     // print_working_directory(path);
//     // {
//     //     // perror("bash$ ");
//     // }
//     // printf("{%s}",getcwd(s, 1000));
//     // path->env->pwd = ft_strdup(s);
//     // puts(path->env->pwd);
// }

char *get_user(char *user)
{
    DIR *dir;
    DIR *dir1;
    struct dirent *sd;
    char *tmp;
    char *p;

    dir = opendir(user);
    if (dir != NULL)
    {
        while ((sd = readdir(dir)) != NULL)
        {
            tmp = ft_strjoin(user, sd->d_name);
            dir1 = opendir(tmp);
            if (dir1)
            {
                closedir(dir1);
                p = ft_strdup(tmp);
                tmp = ft_strjoin(tmp, "/desktop");
                dir1 = opendir(tmp);
                if (dir1)
                {
                    free(tmp);
                    return p;
                }
            }
        }
        closedir(dir);
    }
    return NULL;
}

void cd_cmd(char *nextPath, t_path *path)
{
    char *s;
    if (!nextPath || !ft_strcmp(nextPath, "~"))
        nextPath = get_user("/users/");
    else if( !ft_strncmp(nextPath,"~/",2))
    {
        nextPath = ft_strjoin(get_user("/users/"),(nextPath + 1));
        // printf("\n[%s]\n",nextPath);
    }
    // getcwd(s,100);
    // edit_env(path->env->fullenv,"OLDPWD",s);
    // if(
      if ( chdir(nextPath) < 0)
      {
        ft_putendl_fd(strerror(errno),1);
        //   strerror(errno);
      }
    //    printf("{%d}" ,chdir("/Users/ahaddad"));
    //    perror("bash$ ");
    // getcwd(s,100);
}