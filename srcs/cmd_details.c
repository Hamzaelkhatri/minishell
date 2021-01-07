#include "../includes/minishell.h"

void part_one(t_list_cmd *lst) {
  t_pipe *pipe;
  t_all *all;
  char *string;
  char *str;
  char **tmp;
  char *cmd;
  char *arg;
  char *red;

  pipe = lst->pipe;
  while (lst->pipe != NULL) {
    if (search(lst->pipe->str_pipe) == 1) {
      str = is_after_redirection(lst->pipe->str_pipe);
      string = is_befor_redirection(lst->pipe->str_pipe);
    } else {
      string = ft_strdup(lst->pipe->str_pipe);
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
      if (strcmp(cmd, "echo") == 0 && strcmp(tmp[1], "-n") == 0) {
        cmd = ft_str_join(cmd, " ", tmp[1]);
        arg = concat(tmp, 2);
      } else
        arg = concat(tmp, 1);
    }
    // printf("string: |%s|\n",cmd);
    all = s_cmd_details(cmd, arg, str);
    add_all(&lst->pipe->all, all);
    lst->pipe = lst->pipe->next;
    // return(lst);
  }
  lst->pipe = pipe;
  // print_all(lst);
}

void cmd_details(t_list_cmd *lst) {

  t_all *new1;
  t_list_cmd *lstt;
  t_pipe *pipes;

  lst = link_list(lst);
  lstt = lst;
  while (lst != NULL) {
    if (pipe_e(lst->cmd) == 1) {
      part_one(lst);
    } else {
      if (pipe_e(lst->cmd) == 1)
        lst = lst->next;
      part_two(lst);
    }
    lst = lst->next;
  }
  lst = lstt;
  // print_nested_lklist(lst);
}
