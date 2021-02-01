#include "minishell.h"

int double_red(char *file1, char *file2)
{
    int in, out;

    in = open(file2, O_RDONLY);
    out = open(file1, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
    dup2(in, 0);
    dup2(out, 1);
    close(in);
    close(out);
    return (0);
}
