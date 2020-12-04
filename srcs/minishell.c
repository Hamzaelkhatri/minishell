#include "minishell.h"

int		main(int argc, char **argv,char **env)
{
	t_path path;
	t_key key;
	t_cmd cmd;
	
	 init(&path,&key,&cmd);
	 path.env = env;
	loop_shell(&key,&cmd);
	//    if(ft_str_in_str("dehdehd=","echo"))
    //     {
            
    //     }
	// exeute(path.env);
	return (0);
}

// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <string.h>
// int main(int argc, char **argv,char **env)
// {
// // int status;
// // // pid_t pid;
// // // if((pid = fork())>0)
// // // {
// // //     ///Father process
// // //     wait(&status);
// // //     // printf("Process terminated with status = %d\n",status);
// // // }
// // // else
// // // {
// //     ///son process
// //     int i;
// //     char program[100];

// //     // printf("I'm the son woth PID= %d\n",getpid());
// //     // strcpy(program,argv[1]);

// //     // printf("Program: %s\n", program);
// // 	char *argList[]={"ls",NULL};

// // 	char *envList[] = { "HOME=~/", "/bin", NULL };
// // 	printf("Return is : %i",execve(argList[0],argList,env));
// //     // exit(0);
// // // }         

// loop_shell()
// return 0;
// }