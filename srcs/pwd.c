/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr < helkhatr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 19:15:36 by zjamali           #+#    #+#             */
/*   Updated: 2021/01/07 15:17:26 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_working_directory(t_path *path)
{
	char *pwd;
	pwd = getcwd(NULL,100);
	ft_putendl_fd(pwd,1);
}