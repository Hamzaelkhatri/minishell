#include "minishell.h"

int main(int argc, char **argv, char **env)
{
    int fd;
    t_list_cmd *l_command;
    t_path path;
    t_key key;
    t_cmd cmd;
    char *str;

    l_command = NULL;
    // if()
    fd = open("command.txt", O_RDWR);
    char *line;
    get_next_line(fd, &line);
    ft_check_line(line);
    if (line[0] == '\0')
        return (0);
    l_command = add_list_cmd(l_command);
    l_command->line = ft_strdup(line);
    ft_strdel(&line);

    parse_list_command(l_command, l_command->line);

    // printf("-------------------------------before sort-------------------------------\n");
    // print(l_command);
    sort(l_command);
    // ft_putendl_fd("fena  sat",1);
    quotes(l_command);
    check_scommand(l_command);
    // printf("-------------------------------after sort-------------------------------\n");
    print(l_command);
    free_lcommand(&l_command);
    // printf("-------------------------------echo -n and ignoring quotes-------------------------------\n");
    // print(l_command);
    return (0);
}