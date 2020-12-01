#include "../includes/minishell.h"

char	*read_line(t_key *key)
{
    char	*line;
    int     ret;

    ret = 0;
     
    line = malloc(sizeof(char) * BUFFER_SIZE);
    ft_bzero(line,BUFFER_SIZE);
    if (!line)
    {
        write(1, "bash$> allocation error\n", 30);
        exit(1);
    }
    if ((ret =read(0,line,BUFFER_SIZE)) == -1)
    {
        if(line[BUFFER_SIZE] == '\0')
            exit(0);
        else
            exit(1);   
    }
    if(ret == 0 && key->cntrd !=1)
    {
        ft_putstr_fd("exit", 1);
        exit (1);
    }
    if(ft_strrchr(line, '\n'))
    {
        write(1, "bash$ ", 6);
        key->cntrd = 0;
    }
    else if(ret > 0 && !ft_strrchr(line, '\n'))
       key->cntrd = 1;
    
    return (line);
}

void sigint_handler(int sig)
{
    int a;

    if(sig == SIGINT)
    {
        signal(SIGINT, sigint_handler);
        write(1, "\nbash$ ", 7);
        a = fork();
        if (!a)
        {
            char *cmd[] = {"/bin/stty", 0 };
            char *cmd_args[] = { "stty", "-echoctl", 0 };
            char *env[] = {" ", "env", 0};
            execve(cmd[0], cmd_args, env);
        }
    }
}

void	loop_shell(t_key *key)
{
    char	*line;
    char	**args;
    int		status;
    int		cntrd;
    
    signal(SIGINT, sigint_handler);
    status = 1;
    cntrd = 0;
    ft_putstr_fd("\e[32;40mbash$ ",1);
    // write(1, "bash$ ", 6);
    while (status)
    {
        line = read_line(key);
        free(line);
    }
}