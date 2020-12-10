#include "minishell.h"

t_simple_command *add_node(t_simple_command *node)
{
    t_simple_command *tmp;
    t_simple_command *new;

    tmp = node;
    if (!(new = (t_simple_command *)malloc(sizeof(t_simple_command))))
        return (NULL);
    new->left = NULL;
    new->parent = NULL;
    if (node == NULL)
        return (new);
    while (tmp->left != NULL)
    {
        new->parent = tmp;
        tmp = tmp->left;
    }
    tmp->left = new;
    return (node);
}

t_simple_command *add_data(char *word)
{
    t_simple_command *command;
    command = (t_simple_command *)malloc(sizeof(t_simple_command));
    command->element.word = strdup(word);
    return (command);
}

int check(char *line, char **test)
{
    int i;
    int count;
    int j;

    // tab = 0;
    i = 0;
    count = 0;
    while (line[i])
    {
        if (line[i] == ';' || line[i] == '|')
            count++;
        i++;
    }
    if (count > 0)
    {
        i = 0;
        j = 0;
        *test = malloc((sizeof(char) * count) + 1);
        while (line[i])
        {
            if (line[i] == ';' || line[i] == '|')
            {
                test[0][j] = line[i];
                j++;
            }
            i++;
        }
        test[0][j] = '\0';
    }
    return (count);
}
int main()
{
    int fd;
    fd = open("command.txt", O_RDWR);
    char *line;
    char *test;
    int i = 0;
    get_next_line(fd, &line);
    i = check(line, &test);
    printf("|i==> %d|\t|%s|\n", i, test);
    return (0);
}
// t_simple_command *s_command;
// s_command = NULL;
// s_command = add_node(s_command);
// s_command = add_data("amine sbaa3\n");
// ft_putstr(s_command->element.word);