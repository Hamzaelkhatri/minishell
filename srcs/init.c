/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:10:45 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/19 17:15:25 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void init(t_path *path,t_key *key,t_cmd *cmd)
{
    ft_bzero(key,sizeof(t_key));
    ft_bzero(cmd,sizeof(t_cmd));
    path->key = malloc(sizeof(t_key));
    path->env = malloc(sizeof(t_env));
    // path.env = env;
    // ft_bzero(path->key,sizeof(t_key));
    // path->key->cntrd=0;
    cmd->cd = 0;
    cmd->echo = 0;
    cmd->env = 0;
    cmd->exit = 0;
    cmd->export = 0;
    cmd->pwd = 0;
    cmd->unset = 0;
}


void sh_initial(t_list_cmd *lst, t_shell *sh) {
  sh = malloc(sizeof(t_shell));
  sh->pipe = 0;
  sh->comma = 0;
  sh->count_pipe = 0;

  sh->count_comma = 0;
  ft_bzero(lst, sizeof(t_list_cmd));
}
