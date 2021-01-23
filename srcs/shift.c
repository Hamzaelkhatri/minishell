#include "../includes/minishell.h"

void shift_extra(char *file, char *shifts, t_path *path, t_all *all)
{
    int file_desc;

    file = ft_strtrim(file, "\n");
    all->command = ft_strtrim(all->command, "\n");
    int pid = fork();
    if (pid == 0) {


        if (!ft_strncmp(">>", shifts, 2))
            file_desc = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
        else if (!ft_strncmp(shifts, ">", 1))
            file_desc = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
        if (dup2(file_desc, 1) < 0)
        {
            ft_putendl_fd(strerror(errno), 1);
            exit(EXIT_FAILURE);
        }
        close(file_desc);
        if (ft_strcmp(all->command, "pwd") == 0)
            print_working_directory(path);
        else if (ft_strcmp(all->command, "unset") == 0)
            unset_cmd(all->argument, path);
        else if (ft_strcmp(all->command, "env") == 0)
        {
            show_env(path->env->fullenv);
        }
        else if (ft_strcmp(all->command, "export") == 0)
            export_cmd(all->argument, path->env->fullenv);
        else
        {
            char *binaryPath = "/bin/bash";
            char *const args[] = {binaryPath, "-c", all->command, NULL};
            if (execve(binaryPath, args, path->env->fullenv) == -1)
                perror("bash$ ");
            getprogramme(path, all->command);
        }
        exit(0);
    }
    else
        close(file_desc);
    wait(0);
}