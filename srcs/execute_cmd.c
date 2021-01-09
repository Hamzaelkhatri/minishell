#include "minishell.h"

int get_cmd(char *cmd,t_path *path,t_command *l_cmd)
{

    /*  PIPE : ERROR FOUND IN VAR ENV
    *
    *
    */
    if(!ft_strncmp(cmd,"$",1) && get_var_env(path,cmd))
            cmd = get_var_env(path,cmd);
    if(ft_str_in_str(cmd,"pwd"))
        print_working_directory(path);
    else if(ft_str_in_str(cmd,"env"))
        show_env(path->env->fullenv);
    else if(ft_str_in_str(cmd,"cd"))
    {
        if(l_cmd->s_left->right != NULL)
            cd_cmd(l_cmd->s_left->right->l_element->argument,path);
        else
           cd_cmd(NULL,path);
    }
    else if(ft_str_in_str(cmd,"exit"))
        ft_exit();
    else if(ft_str_in_str(cmd,"export") && l_cmd->s_left->right == NULL)
    {           
        char **tmp = path->env->fullenv;
        ft_sortstr(tmp);
        show_env(tmp);
    }
    else if(ft_str_in_str(cmd,"export") && l_cmd->s_left->right->l_element->argument != NULL)
        export_cmd(l_cmd->s_left->l_element->argument,path->env->fullenv);   
    return 0;
}

int get_cmd_(char *cmd,t_path *path,t_command *l_cmd)
{
    int a;
    char *cmds;
    
    a = 0;
   if(!ft_strncmp(cmd,"$",1) && get_var_env(path,cmd))
    {
        cmd = get_var_env(path,cmd);
        a = 1;
    }
    if(ft_str_in_str(cmd,"pwd"))
        print_working_directory(path);
    else if(ft_str_in_str(cmd,"env"))
        show_env(path->env->fullenv);
    else if(ft_str_in_str(cmd,"cd"))
    {
        if(l_cmd->s_left->right != NULL)
            cd_cmd(l_cmd->s_left->right->l_element->argument,path);
        else
           cd_cmd(NULL,path);
    }
    else if(ft_str_in_str(cmd,"exit"))
        ft_exit();
    else if(ft_str_in_str(cmd,"export") && l_cmd->s_left->right == NULL)
    {           
        char **tmp = path->env->fullenv;
        ft_sortstr(tmp);
        show_env(tmp);
    }
    else if(ft_str_in_str(cmd,"export") && l_cmd->s_left->right->l_element->argument != NULL)
        export_cmd(l_cmd->s_left->l_element->argument,path->env->fullenv);   
    else
    {
            if(a)
                l_cmd->s_left->l_element->cmd = ft_strdup(cmd);
            cmds = ft_strjoin_command(l_cmd->s_left);
            getprogramme(path,cmds);
        wait(0);
    }
    wait(0);
    return 0;
}