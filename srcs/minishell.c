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
    fd = open("command.txt", O_RDWR);
    char *line;
    get_next_line(fd, &line);
    ft_check_line(line);
    if (line[0] == '\0')
        return (0);
    l_command = add_list_cmd(l_command);
    parse_list_command(l_command, line);

    printf("-------------------------------before sort-------------------------------\n");
    print(l_command);
    sort(l_command);
    quotes(l_command);
    check_scommand(l_command);
    printf("-------------------------------after sort-------------------------------\n");
    print(l_command);
    free_lcommand(&l_command);
    ft_strdel(&line);
    // printf("-------------------------------echo -n and ignoring quotes-------------------------------\n");
    // print(l_command);
    return (0);
}