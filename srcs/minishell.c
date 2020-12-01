/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 02:17:32 by helkhatr          #+#    #+#             */
/*   Updated: 2020/12/01 13:15:44 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		main(int argc, char **argv,char **env)
{
	t_path path;
	init(&path);
	path.env = env;
//	printf("%s",search_env(path.env,"PAGER"));
	//show_env(path.env);
	//print_working_directory(path.env); 
	//ft_echo(argv[1],1); // 1 in second argument if -n exist 0 if not
	// loop_shell();
	ft_parse("echo hello | echo -n hello");
	return (0);
}
