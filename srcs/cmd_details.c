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
  t_all *new1;

  pipe = lst->pipe;
  while (lst->pipe != NULL) {
    if (search(lst->pipe->str_pipe) == 1) {
      string = is_befor_redirection(lst->pipe->str_pipe);
      red = is_after_redirection(lst->pipe->str_pipe);
      if (string == NULL) {
        new1 = s_cmd_details(NULL, NULL, red);
        add_all(&lst->pipe->all, new1);
        tmp = ft_space_split(red);
        lst = sort_all_2(lst, lst->pipe->all, red, tmp);
      } else {

        lst = define_each1_02(lst, string, red);
      }
    } else
      lst = sort_all_3(lst);
    lst->pipe = lst->pipe->next;
  }
  lst->pipe = pipe;
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
}
