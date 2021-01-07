/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:30:13 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/07 14:36:41 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void sh_initial(t_list_cmd *lst, t_shell *sh) {
  sh = malloc(sizeof(t_shell));
  sh->pipe = 0;
  sh->comma = 0;
  sh->count_pipe = 0;

  sh->count_comma = 0;
  ft_bzero(lst, sizeof(t_list_cmd));
}

void ch_comma_buil(t_cmd *cmd, char *comnd) {
  cmd->cd = 0;
  cmd->pwd = 0;
  cmd->unset = 0;
  cmd->env = 0;
  cmd->export = 0;
  cmd->echo = 0;
  cmd->exit = 0;
  if (ft_strcmp(comnd, "pwd") == 0)
    cmd->pwd = 1;
  else if (ft_strcmp(comnd, "cd") == 0)
    cmd->cd = 1;
  else if (ft_strcmp(comnd, "unset") == 0)
    cmd->unset = 1;
  else if (ft_strcmp(comnd, "env") == 0)
    cmd->env = 1;
  else if (ft_strcmp(comnd, "cexport") == 0)
    cmd->export = 1;
  else if (ft_strcmp(comnd, "echo") == 0)
    cmd->echo = 1;
  else if (ft_strcmp(comnd, "exit") == 0)
    cmd->exit = 1;
}

void call_getprg(t_list_cmd *lst, t_path *path, t_cmd *cmd) {
  t_list_cmd *tmp;
  t_all *tmp1;
  char *s;
  char *p;

  tmp = lst;
  while (lst != NULL) {
    tmp1 = lst->all;
    while (lst->all != NULL) {
      ch_comma_buil(cmd, lst->all->command);
      if (cmd->pwd == 1)
        print_working_directory(path);
      else if (cmd->export == 1)
        export_cmd(lst->all->argument, path->env->fullenv);
      else if (cmd->cd == 1)
        cd_cmd(lst->all->argument, path);
      else if (cmd->echo == 1) {
      } else if (cmd->env == 1)
        show_env(path->env->fullenv);
      else if (cmd->exit == 1)
        exit(0);
      else if (cmd->unset == 1)
        unset_cmd(lst->all->argument, path);
      else
        getprogramme(path, lst->all->command);
      lst->all = lst->all->next;
    }
    lst->all = tmp1;
    lst = lst->next;
  }
  lst = tmp;
}

// void call_pipe(t_list_cmd *lst, t_path *path, t_shell *sh) {
//   t_list_cmd *list1;
//   t_pipe *pipe;
//   t_all *tmp1;

//   list1 = lst;
//   while (lst != NULL) {
//     if (pipe_e(lst->cmd) == 1)
//       pipes_cmd(path, lst);
//     else {
//       tmp1 = lst->all;
//       while (lst->all != NULL) {
//         getprogramme(path, lst->all->command);
//         lst->all = lst->all->next;
//       }
//       lst->all = tmp1;
//     }
//     lst = lst->next;
//   }
//   lst = list1;
// }
void call_pipe(t_list_cmd *lst, t_path *path, t_shell *sh,t_cmd *cmd)
{
  t_list_cmd *list1;
  t_pipe *pipe;
  t_all *tmp1;

  list1 = lst;
  while (lst != NULL)
  {
    if (pipe_e(lst->cmd) == 1)
    {
      pipes_cmd(path, lst);
    }
    else
    {
      tmp1 = lst->all;
      while (lst->all != NULL)
      {
        call_getprg(lst,path,cmd);
        // getprogramme(path, lst->all->command);
        lst->all = lst->all->next;
      }
      lst->all = tmp1;
    }
    lst = lst->next;
  }
  lst = list1;
}

int main(int argc, char **argv, char **env) {
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
  check_line_error(rd.line);
  sh_initial(&lst, &sh);
  init(&path, &key, &cmd);
  path.env->fullenv = env;
  // show_env(path.env->fullenv);
  lst = *handle_line(&sh, &rd, &lst, env);
  // print_nested_lklist(&lst);
  print_all(&lst);
  // print_working_directory(&path);
  /*------------------check builtins commande--------------*/
  // if (check_one(rd.line, &sh) == 3)
  //   check_built_p(&lst, &cmd);
  // else
  //   check_built(&lst, &cmd);
  // // // /*-----------------for the pipes commande----------------------*/
  // if (check_one(rd.line, &sh) == 1)
  // {
  //   // puts("hola");
  //   pipes_cmd1(&path, &lst, &cmd);
  // }
  // else if (check_one(rd.line, &sh) == 3)
  // {
  //   // puts("dkhal l tanya");
  //   call_pipe(&lst, &path, &sh, &cmd);
  // }else
  //   call_getprg(&lst, &path, &cmd);
  // show_env(env);
  /*--------------------------------------------------------------*/

  // /*----------------end pars $$ begin execution------------------*/
  // path.env->fullenv = env;
  // export_cmd("myvar=300",path.env->fullenv);
  // unset_cmd("_",&path);
  // show_env(path.env->fullenv);
  // cd_cmd("srcs",&path);
  // get_directory(&path);
  // loop_shell(&cmd,&path);
}