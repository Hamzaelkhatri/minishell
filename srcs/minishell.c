/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 02:17:32 by helkhatr          #+#    #+#             */
/*   Updated: 2020/12/08 12:42:44 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		main(int argc, char **argv,char **env)
{
	t_path path;
	t_key key;
	t_cmd cmd;
	
	init(&path,&key,&cmd);
	path.env = env;
	get_directory(&path);
	getprogramme(&path,"ls");//exemple : ls
	// loop_shell(&cmd,&path)
	//init(&path,&key,&cmd);
	//path.env = env;
	//loop_shell(&cmd,&path);
// 	ft_parse("echo  -n 		hello");
	return (0);
}