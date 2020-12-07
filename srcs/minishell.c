/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 02:17:32 by helkhatr          #+#    #+#             */
/*   Updated: 2020/12/07 12:16:06 by zjamali          ###   ########.fr       */
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
	loop_shell(&cmd,&path);
	return (0);
}