#include "minishell.h"

int main(int argc, char **argv, char **env)
{
    int fd;
    t_list_cmd *l_command;
    t_path path;
    t_key key;
    t_cmd cmd;
    // char *str[]={"PATH=\"/Users/helkhatr/Desktop/minishell/minishell_test/bin\"","PWD=\"/Users/helkhatr/Desktop/minishell/minishell_test/sandbox\""};

    l_command = NULL;
    init(&path, &key, &cmd);
    path.cmds= ft_strdup(argv[2]);
    path.env->fullenv = env;
    loop_shell(&path);
    // exit(10);
    // long long 
    // short int i = -2000000;
    // printf("%hd",i);
    return (0);
}
