/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 19:15:36 by zjamali           #+#    #+#             */
/*   Updated: 2020/11/30 19:32:37 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_working_directory(char** env)
{
	char *pwd;
	int i;
	
	i = 0;
	//pwd = search_env(env,"zsh");
	while (env[i])
	{
		if (!ft_strncmp(env[i],"PWD",3))
		{
			pwd = env[i] + 4;
			break;
		}
		i++;
	}
	write(1,pwd,ft_strlen(pwd));
	write(1,"\n",1);
}