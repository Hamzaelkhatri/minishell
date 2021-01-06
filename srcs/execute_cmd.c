#include "minishell.h"

int get_cmd(char *cmd,t_path *path,t_command *l_cmd)
{
    // printf("{pointer ==> %s}\n",l_cmd->s_left->l_element->argument);
    if(ft_str_in_str(cmd,"pwd"))
        print_working_directory(path);
    // if(ft_str_in_str(cmd,"env"))
    //     show_env(path->env->fullenv);
    // if(ft_str_in_str(cmd,"cd"))
    //     cd_cmd(l_cmd->s_left->l_element->argument,path);
    // if(ft_str_in_str(cmd,"exit"))
    //     ft_exit();
    // if(ft_str_in_str(cmd,"export") && l_cmd->s_left->right == NULL)
    // {           
    //     char **tmp = path->env->fullenv;
    //     ft_sortstr(tmp);
    //     show_env(tmp);
    // }
    // if(ft_str_in_str(cmd,"export") && l_cmd->s_left->right->l_element->argument != NULL)
    // {
    //     // printf("wassaap\n");
    //     export_cmd(l_cmd->s_left->l_element->argument,path->env->fullenv);   
    // }
    // if(ft_str_in_str(cmd,"pwd"))
    // {
    //     print_working_directory(path);
    // }    
    return 0;
}