/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:08:10 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/23 15:52:52 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:08:10 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/22 18:56:37 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**************Main zainab*****************/
// int main(int argc, char **argv, char **env)
// {
//   t_read rd;
//   t_shell sh;
//   t_list_cmd lst;
//   t_path path;
//   t_key key;
//   t_cmd cmd;
//   t_pipe pipe;
//   t_all all;

//     ft_bzero(&pipe, sizeof(t_pipe));
//     ft_bzero(&all, sizeof(t_pipe));
//     (void)argc;
//     rd.fd = open("cmd.txt", O_RDONLY);
//     rd.line = malloc(sizeof(char) * BUFFER_SIZE);
//     read(rd.fd, rd.line, BUFFER_SIZE);
//     check_line_error(rd.line,&sh);
//     sh_initial(&lst, &sh);
//     init(&path, &key, &cmd);
//     path.env->fullenv = env;
//     lst = *handle_line(&sh, &rd, &lst, env);
//     print_all(&lst, &sh);


// }
void sigint_handler(int sig)
{
    int a;
    if (sig == SIGINT)
    {
        ft_putstr_fd("\n\e[1;32mbash$ \e[0;37m",1);
        a = fork();
        if (!a)
        {
            char *cmd[] = {"/bin/stty", 0};
            char *cmd_args[] = {"stty", "-echoctl", 0};
            char *env[] = {" ", "env", 0};
            execve(cmd[0], cmd_args, env);
            exit(0);
        }
    }
}
/*****cd *********Main AMINE*****************/
int main(int argc, char **argv, char **env)
{
  t_read rd;
  t_shell sh;
  t_list_cmd lst;
  t_path path;
  t_key key;
  t_cmd cmd;
  t_pipe pipe;
  t_all all;
  
  if (signal(SIGINT, sigint_handler) == SIG_ERR)
    ft_putstr_fd("\n can't catch cnrtl-C", 1);
  if (signal(SIGQUIT, sigint_handler) == SIG_ERR)
    ft_putstr_fd("\n can't catch cntrl-\\", 1);
  while (1)
  {
    ft_putstr_fd("\e[1;32mbash$ \e[0;37m", 1);
    ft_bzero(&pipe, sizeof(t_pipe));
    ft_bzero(&all, sizeof(t_pipe));
    (void)argc;
    rd.fd = open("cmd.txt", O_RDONLY);
    rd.line = malloc(sizeof(char) * BUFFER_SIZE);
    read(0, rd.line, BUFFER_SIZE);
    if (ft_strlen(rd.line) == 0)
    {
      ft_putendl_fd("exit",1);
      exit(0);
    }
    check_line_error(rd.line,&sh);
    sh_initial(&lst, &sh);
    init(&path, &key, &cmd);
    path.env->fullenv = env;
    lst = *handle_line(&sh, &rd, &lst, env);
    // print_all(&lst,&sh);
    if (check_one(rd.line, &sh) == 1)
      pipes_cmd1(&path, &lst, &cmd);
    else if (check_one(rd.line, &sh) == 3)
      call_pipe(&lst, &path, &sh, &cmd);
    else
      call_getprg(&lst, &path, &cmd);
  }
}