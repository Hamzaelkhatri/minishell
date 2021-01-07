/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   details.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 21:44:38 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/07 17:53:16 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_all *s_cmd_details(char *s1, char *s2, char *s3) {
  int i;
  t_all *all;

  i = 0;
  all = malloc(sizeof(t_all));
  all->command = s1;
  all->argument = s2;
  all->redirection = s3;
  all->next = NULL;
  return (all);
}

char **check_each_node(char *line) {

  char **tmp;
  char **tmp1;
  char **tmp2;

  line = befor_direction(line);
  tmp = ft_space_split(line);

  return (tmp);
}
t_list_cmd *link_list(t_list_cmd *lst) {

  t_list_cmd *list1;
  t_shell *sh;
  char **tmp;
  t_pipe *new;
  int i;

  i = 0;
  list1 = lst;
  while (lst != NULL) {
    // puts("im here");

    if (pipe_e(lst->cmd) == 1) {
      i = 0;
      // printf("lst->cmd : %s\n", lst->cmd);
      tmp = ft_split(lst->cmd, '|');
      while (tmp[i] != NULL) {
        tmp[i] = ft_strtrim(tmp[i], " ");
        // printf("=> tmp[i]: %s\n", tmp[i]);
        new = creat_node_p(tmp[i]);
        add_pipe_list(&(lst->pipe), new);
        i++;
      }
    }

    lst = lst->next;
  }
  lst = list1;
  return (lst);
}

void part_two(t_list_cmd *lst) {
  t_all *all;
  char *string;
  char *str;
  char **tmp;
  char *cmd;
  char *arg;
  char *red;

  if (search(lst->cmd) == 1) {
    str = is_after_redirection(lst->cmd);
    string = is_befor_redirection(lst->cmd);
  } else {
    string = ft_strdup(lst->cmd);
    str = NULL;
  }
  tmp = ft_space_split(string);
  if (count_array(tmp) == 2 || count_array(tmp) == 1) {
    cmd = tmp[0];
    arg = tmp[1];
    if (strcmp(cmd, "echo") == 0 && strcmp(arg, "-n") == 0) {
      cmd = ft_str_join(cmd, " ", arg);
      arg = NULL;
    }
  } else {
    cmd = tmp[0];
    if (strcmp(cmd, "echo") == 0 && strcmp(arg, "-n") == 0) {
      cmd = ft_str_join(cmd, " ", tmp[1]);
      arg = concat(tmp, 2);
    } else
      arg = concat(tmp, 1);
  }
  // printf("string: |%s|\n",cmd);
  all = s_cmd_details(cmd, arg, str);
  add_all(&lst->all, all);
}
// void part_one(t_list_cmd *lst)
// {
//   int i;
//   int j;
//   char **tmp2;
//   char **tmp3;
//   char *str1;
//   t_all *new1;
//   t_pipe *pipes;
//   char *cmd;
//   char *arg;

//   pipes = lst->pipe;
//   while (lst->pipe != NULL)
//   {
//     tmp2 = check_each_node(lst->pipe->str_pipe);
//     str1 = in_direction(lst->pipe->str_pipe);
//     i = -1;
//     j = 0;
//     while (tmp2[i + 1])
//     {
//       if (i == -1)
//         i = i + 1;
//       if (ft_strcmp(tmp2[i], "echo") == 0 &&
//           ft_strcmp(tmp2[i + 1], "-n") == 0)
//       {
//         tmp2[i] = ft_strjoin("echo", " -n");
//         if (count_array(tmp2) == 2 || count_array(tmp2) == 1)
//         {
//           cmd = tmp2[0];
//           arg = tmp2[i + 1];
//         }
//         else
//         {
//           cmd = tmp2[0];
//           arg = concat(tmp2);
//         }
//         new1 = s_cmd_details(cmd, arg, str1);
//       }
//       else
//       // printf(" im here");
//       {
//         if (count_array(tmp2) == 2 || count_array(tmp2) == 1)
//         {
//           cmd = tmp2[0];
//           arg = tmp2[i + 1];
//         }
//         else
//         {
//           cmd = tmp2[0];
//           arg = concat(tmp2);
//         }
//         new1 = s_cmd_details(cmd, arg, str1);
//       }
//       add_all(&lst->pipe->all, new1);
//       i = i + 2;
//     }
//     lst->pipe = lst->pipe->next;
//   }
//   lst->pipe = pipes;
//   // printf("==>%d", i);
// }
// void part_two(t_list_cmd *lst)
// {

//   int i;
//   int j;
//   char *str;
//   t_all *new1;
//   char **tmp1;
//   char **tmp;
//   char *cmd;
//   char *arg;

//   tmp = check_each_node(lst->cmd);
//   str = in_direction(lst->cmd);
//   i = -1;
//   j = 0;
//   while (tmp[i + 1])
//   {
//     if (i == -1)
//       i = i + 1;
//     if (ft_strcmp(tmp[i], "echo") == 0 && ft_strcmp(tmp[i + 1], "-n") == 0)
//     {
//       tmp[i] = ft_strjoin("echo", " -n");
//       if (count_array(tmp) == 2 || count_array(tmp) == 1)
//       {
//         cmd = tmp[0];
//         arg = tmp[i + 1];
//       }
//       else
//       {
//         cmd = tmp[0];
//         arg = concat(tmp);
//       }
//       new1 = s_cmd_details(cmd, arg, str);
//     }
//     else
//     {
//       if (count_array(tmp) == 2 || count_array(tmp) == 1)
//       {
//         cmd = tmp[0];
//         arg = tmp[i + 1];
//       }
//       else
//       {
//         cmd = tmp[0];
//         arg = concat(tmp);
//       }
//       new1 = s_cmd_details(cmd, arg, str);
//     }
//     add_all(&lst->all, new1);
//     i = i + 2;
//   }
// }