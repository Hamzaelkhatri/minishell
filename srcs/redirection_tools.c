#include "minishell.h"

int wich_redirection(int check)
{
    if (check == 5 || check == 6 || check == 7 || check == 8)
        return (2);
    else if (check == 1 || check == 2 || check == 3 || check == 4)
        return (1);
    else if (check == 9 || check == 10 || check == 11 || check == 12)
        return (3);
    return (0);
}