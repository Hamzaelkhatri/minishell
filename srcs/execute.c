
#include "minishell.h"

char *strfromto(char *str,int from,char to)
{
    int i;
    char *ret;
    
    i = from;
    ret = malloc(from * sizeof(char));
    // ft_bzero(ret,from);
    while (str[i]!=to)
    {
        //   printf("{%c}",str[i]);
        // if(str[i] != to)
            ret[i] = str[i];
            // printf("%s",&str[from]);
        // else
        //    break;
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
        {
            return (strfromto(str,i,'-'));
        }
        i--;
    }
    return (NULL);
}

void getprogramme(t_path *path,char *cmd)
{
    int i;
    path->pathcmd= search_prev(path->cmds,'+',i);
    exeute(path,cmd);
}

void exeute(t_path *path,char *cmd)
{
    char *programName;
    int i;
    int a = fork();
    // printf("%s",getcwd(programName,100));
    if(!a)
    {
        
        char *binaryPath = "/bin/bash";
        char *const args[] = {binaryPath, "-c", cmd,NULL};
        execve(binaryPath, args, NULL);
    }
    // write(1,"hello",5);
}