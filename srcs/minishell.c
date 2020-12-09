/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr < helkhatr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 02:17:32 by helkhatr          #+#    #+#             */
/*   Updated: 2020/12/09 14:42:46 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		main(int argc, char **argv,char **env)
{
	t_path path;
	t_key key;
	t_cmd cmd;
	char *s;
	
	init(&path,&key,&cmd);
	path.env->fullenv = env;
	cd_cmd("/goinfre/djejd",&path);
	get_directory(&path);
	getprogramme(&path,"ls");
	return (0);
}