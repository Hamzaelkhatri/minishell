#include "minishell.h"

void shift_extra(char *file,char *shifts, t_path *path,t_list_cmd *lst)
{
    int file_desc;

    int pid = fork();
    if (pid == 0)
    {
        if(!ft_strncmp(">>",shifts,2))
            file_desc = open(file,O_WRONLY | O_CREAT | O_APPEND, 0644);
        else if(!ft_strncmp(shifts,">",1))
        {
            file_desc = open(file,O_WRONLY | O_CREAT | O_TRUNC, 0644);
            // printf("\n +++++ \n");
        }
        // printf("%s","holaholaholahoahl");
        dup2(file_desc, 1);
        close(file_desc);
        if (ft_strcmp(lst->all->command, "pwd") == 0)
            print_working_directory(path);
        else if(ft_strcmp(lst->all->command , "unset") == 0)
            unset_cmd(lst->all->argument, path);
        else if(ft_strcmp(lst->all->command , "env") == 0)
            show_env(path->env->fullenv);
        else 
            getprogramme(path, lst->all->command);
        exit(0);
    }
    else
    {
        close(file_desc);
        // wait(0);
    }
}