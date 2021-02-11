/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 19:15:36 by zjamali           #+#    #+#             */
/*   Updated: 2021/02/11 19:30:21 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_working_directory(t_path *path)
{
	char *pwd;

	pwd = getcwd(NULL,100);
	ft_putendl_fd(pwd,1);
	frees(&pwd);
}

void	execute_pwd(char *cmd, t_path *path)
{
	print_working_directory(path);
	path->dollar = 0;
}
