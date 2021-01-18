#include "minishell.h"

char * word_tolower(char *str)
{
    int i;
    char *ptr;

    i = 0;
    ptr = malloc(sizeof(char) * ft_strlen(str));
    while (str[i])
    {
        ptr[i] = ft_tolower(str[i]);
        i++;
    }
    ptr[i] = '\0';
    return (ptr);
}

int get_cmd(char *cmd,t_path *path,t_command *l_cmd)
{
    
    if(!ft_strncmp(cmd,"$",1) && get_var_env(path,cmd))
    {
        cmd = get_var_env(path,cmd);
    }
    else if(ft_strnstr(cmd,"pwd",ft_strlen(cmd)))
       {
            print_working_directory(path);
            path->dollar = 1;
       }
    else if(ft_strnstr(cmd,"env",ft_strlen(cmd)))
        {
            show_env(path->env->fullenv);
            path->dollar = 1;
        }
    else if(ft_strnstr(cmd,"cd",ft_strlen(cmd)))
    {  
        if(l_cmd->s_left->right != NULL)
            cd_cmd(l_cmd->s_left->right->l_element->argument,path);
        else
           cd_cmd(NULL,path);
        path->dollar = 1;
    }
    else if(ft_strnstr(cmd,"exit",ft_strlen(cmd)))
      exit(0);
    else if(ft_strnstr(cmd,"export",ft_strlen(cmd)) && l_cmd->s_left->right == NULL)
    {
        char **tmp = path->env->fullenv;
        ft_sortstr(tmp);
        show_env(tmp);
        path->dollar = 1;
    }
    else if(ft_strnstr(cmd,"export",ft_strlen(cmd)) && l_cmd->s_left->right->l_element->argument != NULL)
        {
            export_cmd(l_cmd->s_left->right->l_element->argument,path->env->fullenv);
       path->dollar = 1;
        }
    else if(ft_strnstr(cmd,"unset",ft_strlen(cmd))&& l_cmd->s_left->right->l_element->argument != NULL)
    {
        unset_cmd(l_cmd->s_left->right->l_element->argument,path);
    }
    return 0;
}

int get_cmd_(char *cmd,t_path *path,t_command *l_cmd)
{
    int a;
    char *cmds;
    
    a = 0;
    cmd = ft_strtrim(cmd,"\n");
    cmd = word_tolower(cmd);
   if(!ft_strncmp(cmd,"$",1) && get_var_env(path,cmd))
    {
        cmd = get_var_env(path,cmd);
        a = 1;
    }
    if(ft_strnstr(cmd,"$?",ft_strlen(cmd)))
    {
           ft_putendl_fd(ft_itoa(path->dollar),1);
    }
    else if(ft_strnstr(cmd,"pwd",ft_strlen(cmd)))
        {
            print_working_directory(path);
            path->dollar = 1;
        }
     else if(ft_strnstr(cmd,"env",ft_strlen(cmd)))
    {
        show_env(path->env->fullenv);
        path->dollar = 1;
    }
     else if(ft_strnstr(cmd,"cd",ft_strlen(cmd)))
    {  
        if(l_cmd->s_left->right != NULL)
            cd_cmd(l_cmd->s_left->right->l_element->argument,path);
        else
           cd_cmd(NULL,path);
        path->dollar = 1;
    }
    else if(ft_strnstr(cmd,"exit",ft_strlen(cmd)))
      exit(0);
    else if(ft_strnstr(cmd,"export",ft_strlen(cmd)) && l_cmd->s_left->right == NULL)
    {
        char **tmp = path->env->fullenv;
        ft_sortstr(tmp);
        show_env(tmp);
        path->dollar = 1;
    }
    else if(ft_strnstr(cmd,"export",ft_strlen(cmd)) && l_cmd->s_left->right != NULL)
    {
        export_cmd(l_cmd->s_left->right->l_element->argument,path->env->fullenv);
    }
    else if(ft_strnstr(cmd,"unset",ft_strlen(cmd))&& l_cmd->s_left->right != NULL)
    {
        unset_cmd(l_cmd->s_left->right->l_element->argument,path);
    }
    // else if(ft_strnstr(cmd,"echo",ft_strlen(cmd)))
    // {
    //     if(l_cmd->s_left->right == NULL)
    //         echo(NULL,path,0);
    //     else
    //         echo(l_cmd->s_left->right->l_element->argument,path,0);
    // }
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