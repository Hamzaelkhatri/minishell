/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 19:15:36 by zjamali           #+#    #+#             */
/*   Updated: 2021/01/06 15:58:30 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	print_working_directory(t_path *path)
// {
// 	char *pwd;

// 	if(!path->env->pwd)
// 	{
// 		pwd = search_env(path->env->fullenv,"PWD");
// 		write(1,pwd,ft_strlen(pwd));
// 	}
// 	else
// 		ft_putstr_fd(path->env->pwd,1);
// }

void print_working_directory(t_path *path) {
  char *pwd;
  pwd = getcwd(path->env->oldpwd, 100);
  // ft_putstr_fd(pwd,1);
  ft_putstr_fd(pwd, 1);
  // if (path->env->pwd == NULL)
  // {
  // printf("\n +++++++++++++++ \n");
  // }
  // path = malloc(sizeof(t_path));
  // path->env->pwd = NULL;
  // if(!path->env->pwd)
  // {
  // 	pwd = search_env(path->env->fullenv,"PWD");
  // 	write(1,pwd,ft_strlen(pwd));
  // }
  // else
  // ft_putstr_fd(search_env(path->env->fullenv,"PWD"),1);
}
