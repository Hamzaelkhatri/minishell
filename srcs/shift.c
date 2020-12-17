#include "minishell.h"

void shift(int fd)
{
    dup2(fd, 1);
}

void shift_extra(char *file,char *shifts)
{
    int file_desc;

    if(!ft_strncmp(">>",shifts,2))
        file_desc = open(file, O_CREAT|O_RDWR|O_APPEND, 0644); // O_APPEND : >> O_TRUNC >
    else if(!ft_strncmp(shifts,">",1))
       	 file_desc = open(file, O_CREAT|O_RDWR|O_TRUNC, 0644); // O_APPEND : >> O_TRUNC >
   
   shift(file_desc);
}
