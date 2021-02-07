#include "minishell.h"

int main(int argc, char **argv, char **env)
{
    int fd;
    t_list_cmd *l_command;
    t_path path;
    t_key key;
    t_cmd cmds;
    t_list_cmd *cmd;
    cmd = NULL;
    l_command = NULL;
    init(&path, &key, &cmds);
    path.env->fullenv = env;
    // get_directory(&path, "ls");
    loop_shell(&path,cmd);
    return (0);
}
