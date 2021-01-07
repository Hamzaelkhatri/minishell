/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:55:48 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/07 18:47:53 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *seperat_red(char *tmp) {
  int i;
  int j;
  char *res;

  i = 0;
  j = 0;
  if (!(res = malloc(sizeof(char) * 2)))
    return (NULL);
  while (tmp[i] != '\0') {
    if ((tmp[i] == '>' && tmp[i + 1] != '>') || tmp[i] == '<') {
      res[0] = tmp[i];
      res[1] = '\0';
      break;
    } else if ((tmp[i] == '>' && tmp[i + 1] == '>')) {
      res = ft_strdup(">>");
      break;
    } else {
      i++;
    }
  }
  return (res);
}
char *seperat_file_name(char *tmp) {
  int i;
  int j;
  char *res;

  i = 0;
  j = 0;
  if (!(res = malloc(sizeof(char) * (strlen(tmp)))))
    return (NULL);
  while (tmp[i] != '\0') {
    if ((tmp[i] == '>' && tmp[i + 1] != '>') || tmp[i] == '<')
      i++;
    else if ((tmp[i] == '>' && tmp[i + 1] == '>'))
      i = i + 2;
    else {
      res[j] = tmp[i];
      j++;
      i++;
    }
  }
  res[j] = '\0';
  return (res);
}

int condition_1(char **free_sp, int i) {
  if (check_redirection(free_sp[i]) != 0 && free_sp[i + 1] != NULL &&
      (strcmp(free_sp[i], ">>") == 0 || strcmp(free_sp[i], ">") == 0 ||
       strcmp(free_sp[i], "<") == 0))
    return (1);
  else
    return (0);
}
int condition_2(char **free_sp, int i) {
  if (check_redirection(free_sp[i]) != 0 &&
      (strcmp(free_sp[i], ">>") != 0 || strcmp(free_sp[i], ">") != 0 ||
       strcmp(free_sp[i], "<") != 0))
    return (1);
  else
    return (0);
}

t_all *all_conditions(t_all *all, char **free_sp, int *i) {
  t_use use;
  ft_bzero(&use, sizeof(t_use));

  if (condition_1(free_sp, *i) == 1) {
    use.red1 = creat_node_r(free_sp[*i], free_sp[(*i) + 1]);
    add_red(&all->red, use.red1);
    *i = *i + 2;
  } else if (condition_2(free_sp, *i) == 1) {
    use.sign = seperat_red(free_sp[*i]);
    use.file_name = seperat_file_name(free_sp[*i]);
    use.red1 = creat_node_r(use.sign, use.file_name);
    add_red(&all->red, use.red1);
    *i = *i + 1;
  }
  return (all);
}
void condition_3(t_use *use, char ***free_sp) {
  if (use->cmd_index == 0) {
    use->cmd2 = ft_strdup((*free_sp)[use->i]);
    use->cmd_index = 1;
    use->i++;
  } else {
    use->arg = ft_strjoin((*free_sp)[use->i], " ");
    use->arg1 = concat_1(use->arg, use->arg1);
    use->i++;
  }
}
t_list_cmd *sort_all_2(t_list_cmd *lst, t_all *all, char *red, char **free_sp) {
  t_use use;
  ft_bzero(&use, sizeof(t_use));

  while (free_sp[use.i] != NULL) {
    if (condition_1(free_sp, use.i) == 1 || condition_2(free_sp, use.i) == 1)
      all = all_conditions(all, free_sp, &use.i);
    else
      condition_3(&use, &free_sp);
    lst->all = update_all(use.cmd2, use.arg1, all->red);
  }
  return (lst);
}