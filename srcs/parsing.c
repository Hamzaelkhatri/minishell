/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 16:39:14 by zdnaya            #+#    #+#             */
/*   Updated: 2020/12/25 14:47:21 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
// https://guide.bash.academy/commands/

void ft_check_comma(char *line, t_shell *sh) {
  int i;

  i = 0;
  sh->comma = 0;
  while (line[i]) {
    if (line[i] == ';') {
      sh->comma = 1;
    }
    i++;
  }
}
void ft_check_pipe(char *line, t_shell *sh) {
  int i;

  i = 0;
  // printf(" im here");
  sh->pipe = 0;
  while (line[i]) {
    if (line[i] == '|') {
      sh->pipe = 1;
    }
    i++;
  }
}

t_list_cmd *handle_line(t_shell *sh, t_read *rd, t_list_cmd *lst, char **env) {
  t_list_cmd *new;
  int i;

  i = 0;
  lst = NULL;

  ft_check_pipe(rd->line, sh);
  ft_check_comma(rd->line, sh);

  if (sh->pipe == 1 && sh->comma == 0)
    sh->simple_cmd = ft_split(rd->line, '|');
  else if (sh->comma == 1)
    sh->simple_cmd = ft_split(rd->line, ';');
  else
    sh->simple_cmd = ft_split(rd->line, '\0');
  while (sh->simple_cmd[i] != NULL) {
    // printf("**%s**\n", sh->simple_cmd[i]);
    sh->simple_cmd[i] = ft_strtrim(sh->simple_cmd[i], " ");

    new = creat_node(sh->simple_cmd[i]);
    add_cmd(&lst, new);
    i++;
  }
  if (sh->pipe == 1 && sh->comma == 1) {
    // puts("here");
    
    seperat_with_pipe(lst, sh);
    pipe_define_each(lst, sh, env);
  }
  else
    define_each(lst, sh, env);
  return (lst);
}

t_list_cmd *define_each(t_list_cmd *lst, t_shell *sh, char **env) {
  char **tmp;
  int i;
  int j;

  i = 0;
  j = 0;
  tmp = NULL;
  t_list_cmd *lst1;
  lst1 = lst;

  while (lst != NULL) {
    tmp = ft_space_split(lst->cmd);
    lst->sh_cmd = tmp[0];
    lst->sh_arg = tmp[1];
    // printf("|=>|%s|\n",lst->sh_arg);
    // i++;
    lst = lst->next;
  }
  lst1 = lst;
  return (lst);
}