/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr < helkhatr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 19:15:36 by zjamali           #+#    #+#             */
/*   Updated: 2021/01/05 17:38:47 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_working_directory(t_path *path)
{
	char *pwd;
	char *pwd1;
	pwd1=ft_strdup("");
	pwd = getcwd(pwd1,100);
	ft_putstr_fd(pwd,1);
	free(pwd1);
}