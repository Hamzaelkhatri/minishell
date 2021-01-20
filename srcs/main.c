/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:08:10 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/20 14:36:35 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


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
  while (1)
  {
    ft_putstr_fd("\e[1;32mbash$ \e[0;37m", 1);
    ft_bzero(&pipe, sizeof(t_pipe));
    ft_bzero(&all, sizeof(t_pipe));
    (void)argc;
    rd.fd = open("cmd.txt", O_RDONLY);
    rd.line = malloc(sizeof(char) * BUFFER_SIZE);
    read(0, rd.line, BUFFER_SIZE);
    // {
    //   write(1," \n",2);
    //   exit(1);
    // }
    check_line_error(rd.line,&sh);
    sh_initial(&lst, &sh);
    init(&path, &key, &cmd);
    path.env->fullenv = env;
    lst = *handle_line(&sh, &rd, &lst, env);
    // print_all(&lst);
    if (check_one(rd.line, &sh) == 1)
      pipes_cmd1(&path, &lst, &cmd);
    else if (check_one(rd.line, &sh) == 3)
      call_pipe(&lst, &path, &sh, &cmd);
    else
      call_getprg(&lst, &path, &cmd);
  }
}