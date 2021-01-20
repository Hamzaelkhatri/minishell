/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 16:34:39 by ahaddad           #+#    #+#             */
/*   Updated: 2021/01/18 10:51:26 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void check_built(t_list_cmd *lst, t_cmd *cmd) {
  t_all *all;
  t_list_cmd *tmp;

  tmp = lst;
  while (lst != NULL) {
    // puts("ana hna ");
    all = lst->all;
    while (lst->all != NULL) {
      // printf("cmd : |%s|\n", lst->all->command);
      // printf(" arg :|%s|\n", lst->all->argument);
      if ((ft_strlen(lst->all->command) == 4) &&
          !ft_strncmp(lst->all->command, "echo", 4)) {
        cmd->echo = 1;
        // puts("echo hna");
        if (!ft_strncmp(lst->all->command, "echo -n", 7))
          ft_echo(lst->all->argument, 1);
      } else if ((ft_strlen(lst->all->command) == 2) &&
                 !ft_strncmp(lst->all->command, "cd", 2))
        cmd->cd = 1;
      else if ((ft_strlen(lst->all->command) == 3) &&
               !ft_strncmp(lst->all->command, "pwd", 3))
        cmd->pwd = 1;
      else if ((ft_strlen(lst->all->command) == 6) &&
               !ft_strncmp(lst->all->command, "export", 6))
        cmd->export = 1;
      else if ((ft_strlen(lst->all->command) == 5) &&
               !ft_strncmp(lst->all->command, "unset", 5))
        cmd->unset = 1;
      else if ((ft_strlen(lst->all->command) == 3) &&
               !ft_strncmp(lst->all->command, "env", 3))
        cmd->env = 1;
      else if ((ft_strlen(lst->all->command) == 4) &&
               !ft_strncmp(lst->all->command, "exit", 4))
        cmd->exit = 1;

      lst->all = lst->all->next;
    }
    lst->all = all;
    lst = lst->next;
  }
  lst = tmp;
}
void check_built_p(t_list_cmd *lst, t_cmd *cmd, t_shell *sh) {
  t_pipe *tmp1;
  t_all *all;
  t_list_cmd *list1;

  list1 = lst;
  while (lst != NULL) {

    // printf("cmd : |%s|\n", lst->cmd);
    // printf("%d\n", pipe_e(lst->cmd));

    if (pipe_e(lst->cmd, sh) == 1) {
      //   puts(" im here");
      tmp1 = lst->pipe;
      while (lst->pipe != NULL) {
        all = lst->pipe->all;
        while (lst->pipe->all != NULL) {
          //   printf(" arg :|%s|\n", lst->pipe->all->argument);
          //   puts(" ana fi PIPe");
          if ((ft_strlen(lst->pipe->all->command) == 4) &&
              !ft_strncmp(lst->pipe->all->command, "echo", 4)) {
            cmd->echo = 1;
            // puts("le9it echo");
            if (!ft_strncmp(lst->pipe->all->command, "echo -n", 7))
              ft_echo(lst->pipe->all->argument, 1);
          } else if ((ft_strlen(lst->pipe->all->command) == 2) &&
                     !ft_strncmp(lst->pipe->all->command, "cd", 2)) {
            cmd->cd = 1;
            // puts("le9it cd");
          } else if ((ft_strlen(lst->pipe->all->command) == 3) &&
                     !ft_strncmp(lst->pipe->all->command, "pwd", 3)) {
            cmd->pwd = 1;
            // puts("le9it pwd");
          } else if ((ft_strlen(lst->pipe->all->command) == 6) &&
                     !ft_strncmp(lst->pipe->all->command, "export", 6)) {

            cmd->export = 1;
            // puts("le9it export");
          } else if ((ft_strlen(lst->pipe->all->command) == 5) &&
                     !ft_strncmp(lst->pipe->all->command, "unset", 5)) {
            cmd->unset = 1;
            // puts("le9it echo");
          } else if ((ft_strlen(lst->pipe->all->command) == 3) &&
                     !ft_strncmp(lst->pipe->all->command, "env", 3))
            cmd->env = 1;
          else if ((ft_strlen(lst->pipe->all->command) == 4) &&
                   !ft_strncmp(lst->pipe->all->command, "exit", 4))
            cmd->exit = 1;
          lst->pipe->all = lst->pipe->all->next;
        }
        lst->pipe->all = all;
        lst->pipe = lst->pipe->next;
      }
      lst->pipe = tmp1;
    } else {
      while (lst->all != NULL) {
        // printf("cmd : |%s|\n", lst->all->command);
        // printf(" arg :|%s|\n", lst->all->argument);
        if ((ft_strlen(lst->all->command) == 4) &&
            !ft_strncmp(lst->all->command, "echo", 4)) {
          cmd->echo = 1;
          // puts("echo hna");
          if (!ft_strncmp(lst->all->command, "echo -n", 7))
            ft_echo(lst->all->argument, 1);
        } else if ((ft_strlen(lst->all->command) == 2) &&
                   !ft_strncmp(lst->all->command, "cd", 2))
          cmd->cd = 1;
        else if ((ft_strlen(lst->all->command) == 3) &&
                 !ft_strncmp(lst->all->command, "pwd", 3))
          cmd->pwd = 1;
        else if ((ft_strlen(lst->all->command) == 6) &&
                 !ft_strncmp(lst->all->command, "export", 6))
          cmd->export = 1;
        else if ((ft_strlen(lst->all->command) == 5) &&
                 !ft_strncmp(lst->all->command, "unset", 5))
          cmd->unset = 1;
        else if ((ft_strlen(lst->all->command) == 3) &&
                 !ft_strncmp(lst->all->command, "env", 3))
          cmd->env = 1;
        else if ((ft_strlen(lst->all->command) == 4) &&
                 !ft_strncmp(lst->all->command, "exit", 4))
          cmd->exit = 1;

        lst->all = lst->all->next;
      }
    }
    lst = lst->next;
  }
}

//   } else {
//     puts("ana hna ");
//     all = NULL;
//     all = lst->all;
//   tmp = lst;
//   while (lst != NULL) {

// lst = lst->next;
//   }
//   lst = tmp;
// }
// lst->all = all;
// }

// lst = lst->next;
// }
// lst = list1;
// }
