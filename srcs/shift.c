#include "minishell.h"

void shift(int fd)
{
    dup2(fd, 1);
    close(fd);
}

void shift_extra(char *file,char *shifts, t_path *path,t_list_cmd *lst)
{
    int file_desc;

    int pid = fork();
    if (pid == 0)
    {
        if(!ft_strncmp(">>",shifts,2))
            file_desc = open(file,O_WRONLY | O_CREAT | O_APPEND, 0777);
        else if(!ft_strncmp(shifts,">",1))
        {
            file_desc = open(file,O_WRONLY | O_CREAT | O_TRUNC, 0777);
            // printf("\n +++++ \n");
        }
        // printf("%s","holaholaholahoahl");
        if(dup2(file_desc, 1)<0)
        {
           ft_putendl_fd(strerror(errno),1);
            exit(EXIT_FAILURE);
        }
        if (ft_strcmp(lst->all->command, "pwd") == 0)
            print_working_directory(path);
        else if(ft_strcmp(lst->all->command , "unset") == 0)
            unset_cmd(lst->all->argument, path);
        else if(ft_strcmp(lst->all->command , "env") == 0)
            export_cmd(lst->all->argument,path->env->fullenv);
        else 
            getprogramme(path, lst->all->command);
        close(file_desc);
        exit(0);
    }
    else
    {
        close(file_desc);
    }
    wait(0);
}