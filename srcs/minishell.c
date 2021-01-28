#include "minishell.h"


char **argss(char *cmd,t_path *path)
{
    char **split;
    split = ft_split(cmd, ' ');

    split[0]=get_directory(path, cmd);
    return (split);
}


int main(int argc, char **argv, char **env)
{
    int fd;
    t_list_cmd *l_command;
    t_path path;
    t_key key;
    t_cmd cmd;
    l_command = NULL;
    init(&path, &key, &cmd);
    path.env->fullenv = env;
    // show_env(argss("ls /",&path));
    // puts();
    // puts(get_directory(&path,"ls"));
    // puts(get_directory(&path,"/bin/ls"));
    loop_shell(&path);
    return (0);
}
