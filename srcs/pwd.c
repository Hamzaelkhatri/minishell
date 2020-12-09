/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr < helkhatr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 19:15:36 by zjamali           #+#    #+#             */
/*   Updated: 2020/12/09 14:37:46 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_working_directory(t_path *path)
{
	char *pwd;
	
	if(!path->env->pwd)
	{
		pwd = search_env(path->env->fullenv,"PWD");
		write(1,pwd,ft_strlen(pwd));
	}
	else
		ft_putstr_fd(path->env->pwd,1);
}