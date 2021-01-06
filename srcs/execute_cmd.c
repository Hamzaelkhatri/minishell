#include "minishell.h"

int get_cmd(char *cmd,t_path *path,t_command *l_cmd)
{
    if(ft_str_in_str(cmd,"pwd"))
        print_working_directory(path);
    else if(ft_str_in_str(cmd,"env"))
        show_env(path->env->fullenv);
    else if(ft_str_in_str(cmd,"cd"))
        cd_cmd(l_cmd->s_left->l_element->argument,path);
    else if(ft_str_in_str(cmd,"exit"))
        ft_exit();
    else if(ft_str_in_str(cmd,"export") && l_cmd->s_left->right == NULL)
    {           
        char **tmp = path->env->fullenv;
        ft_sortstr(tmp);
        show_env(tmp);
    }
    else if(ft_str_in_str(cmd,"export") && l_cmd->s_left->right->l_element->argument != NULL)
    {
        export_cmd(l_cmd->s_left->l_element->argument,path->env->fullenv);   
    }
    return 0;
}

int get_cmd_(char *cmd,t_path *path,t_command *l_cmd)
{
    int a;
    char *cmds;
	char *binaryPath = "/bin/bash";

    if(ft_str_in_str(cmd,"pwd"))
        print_working_directory(path);
    else if(ft_str_in_str(cmd,"env"))
        show_env(path->env->fullenv);
    else if(ft_str_in_str(cmd,"cd"))
        cd_cmd(l_cmd->s_left->l_element->argument,path);
    else if(ft_str_in_str(cmd,"exit"))
        ft_exit();
    else if(ft_str_in_str(cmd,"export") && l_cmd->s_left->right == NULL)
    {           
        char **tmp = path->env->fullenv;
        ft_sortstr(tmp);
        show_env(tmp);
    }
    else if(ft_str_in_str(cmd,"export") && l_cmd->s_left->right->l_element->argument != NULL)
    {
        export_cmd(l_cmd->s_left->l_element->argument,path->env->fullenv);   
    }
    else
    {
        a = fork();
        if(!a)
        {
            cmds = ft_strjoin_command(l_cmd->s_left);
            char *const args[] = {binaryPath, "-c", cmds,NULL};
            if (execve(binaryPath, args, NULL) < 0)
            perror("bash$ :");
            free(cmds);
            exit(0);
        }
        waitpid(-1,0,0);
    }
    
    return 0;
}