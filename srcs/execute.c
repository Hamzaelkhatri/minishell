
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

    i = check_path(path->cmds,cmd);
    if(!i)
        printf("bash$ commande not found");
    else
    {
        path->pathcmd= search_prev(path->cmds,'+',i);
        exeute(path,cmd);
    }
}

void exeute(t_path *path,char *cmd)
{
    char *programName;
    int i;
    char *binaryPath = "/bin/bash";
	char *const args[] = {binaryPath, "-c", cmd,NULL};
    execve(binaryPath, args, NULL);
    // programName = malloc(ft_strlen(path->pathcmd)+ft_strlen(cmd)+1);
    // programName=ft_strjoin(programName,path->pathcmd);
    // programName=ft_strjoin(programName,"/");
    // programName = ft_strjoin(programName,cmd);
    // // printf("[%s]",programName);
    // char *args[] = {programName,".", NULL};
    // int c = execvp(programName, args);
    // if(c == -1)
    // {
    //     i = check_path(path->cmds,cmd)+ft_strlen(cmd);
    //     // path->cmds = &path->cmds[i]
    //     getprogramme(path,cmd,i);
    //     // printf("%s",&path->cmds[i]);
    // }
}