#include "minishell.h"

int check_char(char *src,char *dst)
{
    int i = 0;
    int j = 0;
    if(ft_strlen(src) != ft_strlen(dst))
        return (0);
    while(src[i])
    {
        if(src[i] == dst[i])
        {
            j = i;
            while(dst[j])
            {
                if(dst[j] != src[j])
                    break;
                if(!dst[j+1])
                    return (1);
                j++;
            }
        }
        i++;
    }
    return (0);
}

int cmdcheck(char *str)
{
    char *cmd[9];
    int i;
    
    i = 0;
    cmd[0] = "echos";
    cmd[1] = "exit";
    cmd[2] = "env";
    cmd[3] = "export";
    cmd[4] = "unset";
    cmd[5] = "pwd";
    cmd[6] = "cd";
    cmd[7] = NULL;
    while (cmd[i])
    {
        if(check_char(cmd[i],str))
            return (1);
        i++;
    }
    return (0);
}