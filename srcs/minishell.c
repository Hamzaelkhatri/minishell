#include "minishell.h"

int main(int argc, char **argv, char **env)
{
    int fd;
    t_list_cmd *l_command;
    t_path path;
    t_key key;
    t_cmd cmd;

    l_command = NULL;
    // fd = open("command.txt", O_RDWR);
    char *line;
    // get_next_line(fd, &line);
    // line = malloc(sizeof(char)*5000);
    // read(fd,line,5000);
   
    init(&path, &key, &cmd);
    path.env->fullenv = env;

    
    loop_shell(&path);
    // print(l_command);
    // printf("%s",l_command->command->s_left->right->l_element->cmd); 
    // shift_extra(l_command->command->s_left->right->l_element->redirection.file,l_command->command->s_left->right->l_element->redirection.i_o);
   
    // free_lcommand(&l_command);
    ft_strdel(&line);


    
    return (0);
}