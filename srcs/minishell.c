/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr < helkhatr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 02:17:32 by helkhatr          #+#    #+#             */
/*   Updated: 2020/12/16 13:59:41 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv,char **env)
{
	t_path path;
	t_key key;
	t_cmd cmd;
	char *s;
	
	init(&path,&key,&cmd);
	path.env->fullenv = env;
	 //get_directory(&path);
	// loop_shell(&cmd,&path);
	
	//shift_extra("tricky.txt",">");
	get_var_env(&path,"$ORIGINAL_XDG_CURRENT_DESKTOP");
	show_env(path.env->fullenv);
	// getprogramme(&path,"ls | cat");
	return (0);
}