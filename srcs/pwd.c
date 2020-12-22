/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 19:15:36 by zjamali           #+#    #+#             */
/*   Updated: 2020/12/22 13:15:26 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_working_directory(t_path *path)
{
	char *pwd;

	if (!path->env->pwd)
	{
		pwd = search_env(path->env->fullenv, "PWD");
		write(1, pwd, ft_strlen(pwd));
	}
	else
		ft_putstr_fd(path->env->pwd, 1);
}