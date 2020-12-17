
#include "minishell.h"

char *strfromto(char *str,int from,char to)
{
    int i;
    char *ret;
    
    i = from;
    ret = malloc(from * sizeof(char));
    while (str[i]!=to)
    {
        ret[i] = str[i];
        i++;
    }
    ret[i]='\0';
    return (&ret[1]);
}

char *search_prev(char *str,char c,int i)
{
    char *ptr;
    while (i>=0)
    {
        if(str[i]==c)
            return (strfromto(str,i,'-'));
        i--;
    }
    return (NULL);
}

void getprogramme(t_path *path,char *cmd)
{
    int i;
    exeute(path,cmd);
}

void exeute(t_path *path,char *cmd)
{
    int a = fork();
    if(!a)
    {
        char *binaryPath = "/bin/bash";
        char *const args[] = {binaryPath, "-c", cmd,NULL};
        if(execve(binaryPath, args, NULL)==-1)
            perror("bash$ ");

    }
}
