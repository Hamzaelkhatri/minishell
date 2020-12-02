/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr < helkhatr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 02:17:32 by helkhatr          #+#    #+#             */
/*   Updated: 2020/12/02 12:07:26 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv,char **env)
{
	t_path path;
	t_key key;
	
	init(&path,&key);
	path.env = env;
	loop_shell(&key);
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