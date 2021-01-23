/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:08:10 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/23 15:21:56 by zdnaya           ###   ########.fr       */
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

    ft_bzero(&pipe, sizeof(t_pipe));
    ft_bzero(&all, sizeof(t_pipe));
    (void)argc;
    rd.fd = open("cmd.txt", O_RDONLY);
    rd.line = malloc(sizeof(char) * BUFFER_SIZE);
    read(rd.fd, rd.line, BUFFER_SIZE);
    check_line_error(rd.line,&sh);
    sh_initial(&lst, &sh);
    init(&path, &key, &cmd);
    path.env->fullenv = env;
    lst = *handle_line(&sh, &rd, &lst, env);
    print_all(&lst, &sh);


}
/*****cd *********Main AMINE*****************/
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
//   while (1)
//   {
//     ft_putstr_fd("\e[1;32mbash$ \e[0;37m", 1);
//     ft_bzero(&pipe, sizeof(t_pipe));
//     ft_bzero(&all, sizeof(t_pipe));
//     (void)argc;
//     rd.fd = open("cmd.txt", O_RDONLY);
//     rd.line = malloc(sizeof(char) * BUFFER_SIZE);
//     read(0, rd.line, BUFFER_SIZE);
//     check_line_error(rd.line,&sh);
//     sh_initial(&lst, &sh);
//     init(&path, &key, &cmd);
//     path.env->fullenv = env;
//     lst = *handle_line(&sh, &rd, &lst, env);
//     // print_all(&lst,&sh);
//     if (check_one(rd.line, &sh) == 1)
//       pipes_cmd1(&path, &lst, &cmd);
//     else if (check_one(rd.line, &sh) == 3)
//       call_pipe(&lst, &path, &sh, &cmd);
//     else
//       call_getprg(&lst, &path, &cmd);
//   }
// }