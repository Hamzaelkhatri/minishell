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
    int exits = 0;
    cmd = ft_strtrim(cmd,"\n");
    cmd = word_tolower(cmd);
    //  puts("HERE"); 
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
        {
            exit(0);
        }
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
    return (1);
}

int count_digit(char *str)
{
    int i = 0;
    int c = 0;
    while (str[i] == '0')
        i++;
    while (str[i])
    {
        c++;
        i++;
    }
    return (c);
}

int is_int(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if(!ft_isdigit(str[i]))
            return 0;
        i++;
    }
    return 1;
}

long long ft_atoi_long(char* str)
{
    int i;
	int sign;
	long long result;
	int counter;

	i = 0;
	sign = 1;
	result = 0;
	counter = 0;

	while (str[i] == ' ' || str[i] == '\r' || str[i] == '\f' || str[i] == '\n'
			|| str[i] == '\v' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1 * sign;
		i++;
	}
	while (str[i]=='0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
		counter++;
	}
	return (result * sign);
}

void print_err_exite(char *s)
{
    ft_putstr_fd("minishell: exit: ",2);
    ft_putstr_fd(s,2);
    ft_putendl_fd(": numeric argument required",2);
}

int	check_int(char *str)
{
	int	i;

	i = 0;
    str = ft_strtrim(str,"\n");
    str = ignoring_quote(str);
    while (str[i] && str[i] < 33)
        i++;
    if(str[i] == '-' || str[i] == '+')
        i++;
    if(ft_atoi_long(str) <= LLONG_MIN && str[i-1]!='-')
    {
        print_err_exite(str);
         return (255);
    }
    if (ft_atoi_long(str) < LLONG_MIN)
    {
         print_err_exite(str);
         return (0);
    }
    else if(ft_atoi_long(str) > LLONG_MAX)
    {
         print_err_exite(str);
         return (255);
    }
    else if(ft_atoi_long(str) <= LONG_MIN && count_digit(&str[i]) == 19)
    {
         return (0);
    }
    else if(count_digit(&str[i]) == 19 && str[i-1] == '-')
    {
         print_err_exite(str);
         return (255);
    }
	while (str[i])
	{
        
		if((!ft_isdigit(str[i]) && str[i] != 32 && str[i] != '\t' )||count_digit(&str[i])>19)
    	{
            print_err_exite(str);
            return (255);
        }
		i++;
	}
	return (ft_atoi(str));
}


int size_args(t_command *l_cmd)
{
    int i;
    t_simple_command *tmp;

    tmp = l_cmd->s_left->right;
    i = 0;
    while (tmp)
    {
        i++;
        tmp = tmp->right;
    }
    return (i);    
}

int get_cmd_(char *cmd,t_path *path,t_command *l_cmd)
{
    int a;
    char *cmds;
    
    a = 0;
    cmd = ft_strtrim(cmd,"\n");
   if(!ft_strncmp(cmd,"$",1) && get_var_env(path,cmd))
    {
        cmd = get_var_env(path,cmd);
        a = 1;
    }
    if(!ft_strnstr("exit",word_tolower(cmd),ft_strlen(cmd)))
        cmd = word_tolower(cmd);
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
    {

        if(size_args(l_cmd)>1 && is_int(l_cmd->s_left->right->l_element->argument))
        {
            ft_putendl_fd("minishell: exit: too many arguments",2);
            exit(EXIT_FAILURE);
        }
        if(l_cmd->s_left->right)
            exit(check_int(l_cmd->s_left->right->l_element->argument));
        else
            exit(EXIT_SUCCESS);
        
    }
    else if(ft_strnstr(cmd,"export",ft_strlen(cmd)) && l_cmd->s_left->right == NULL)
    {
        char **tmp = path->env->fullenv;
        ft_sortstr(tmp);
        show_export(tmp);
        path->dollar = 1;
    }
    else if(ft_strnstr(cmd,"export",ft_strlen(cmd)) && l_cmd->s_left->right != NULL)
    {
        while (l_cmd->s_left->right)
        {
            if(!export_cmd(l_cmd->s_left->right->l_element->argument,path->env->fullenv))
                break;
            l_cmd->s_left->right=l_cmd->s_left->right->right;
        }
        
    }
    else if(ft_strnstr(cmd,"unset",ft_strlen(cmd))&& l_cmd->s_left->right != NULL)
    {
        unset_cmd(l_cmd->s_left->right->l_element->argument,path);
    }
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