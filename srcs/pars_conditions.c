/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_conditions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:24:06 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/23 12:50:20 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int condition_1(char **free_sp, int i)
{

  if (check_redirection(free_sp[i]) != 0 && free_sp[i + 1] != NULL &&
      (strcmp(free_sp[i], ">>") == 0 || strcmp(free_sp[i], ">") == 0 ||
       strcmp(free_sp[i], "<") == 0))
    return (1);
  else
    return (0);
}
int condition_2(char **free_sp, int i)
{
  if (check_redirection(free_sp[i]) != 0 &&
      (strcmp(free_sp[i], ">>") != 0 || strcmp(free_sp[i], ">") != 0 ||
       strcmp(free_sp[i], "<") != 0))
    return (1);
  else
    return (0);
}

t_all *all_conditions(t_all *all, char **free_sp, int *i)
{
  t_use use;

  ft_bzero(&use, sizeof(t_use));
  if (condition_1(free_sp, *i) == 1)
  {
    use.red1 = creat_node_r(free_sp[*i], free_sp[(*i) + 1]);
    add_red(&all->red, use.red1);
    *i = *i + 2;
  }
  else if (condition_2(free_sp, *i) == 1)
  {
    use.sign = seperat_red(free_sp[*i]);
    use.file_name = seperat_file_name(free_sp[*i]);
    use.red1 = creat_node_r(use.sign, use.file_name);
    add_red(&all->red, use.red1);
    *i = *i + 1;
  }
  return (all);
}
void condition_3(t_use *use, char ***free_sp)
{
  if (use->cmd_index == 0)
  {
    use->cmd2 = ft_strdup(no_quote((*free_sp)[use->i]));
    use->cmd_index = 1;
    use->i++;
  }
  else
  {
    use->arg = ft_strjoin(no_quote((*free_sp)[use->i]), " ");
    use->arg1 = concat_space(use->arg, use->arg1);
    use->i++;
  }
}