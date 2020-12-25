#include "minishell.h"

void shift(int fd)
{
    dup2(fd, 1);
}

void shift_extra(char *file,char *shifts)
{
    int file_desc;

    if(!ft_strncmp(">>",shifts,2))
        file_desc = open(file,O_WRONLY | O_CREAT | O_APPEND, 644); // O_APPEND : >> O_TRUNC >
    else if(!ft_strncmp(shifts,">",1))
            file_desc = open(file,O_WRONLY | O_CREAT | O_TRUNC, 644); // O_APPEND : >> O_TRUNC >
   
   shift(file_desc);
}