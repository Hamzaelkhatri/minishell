/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 02:17:32 by helkhatr          #+#    #+#             */
/*   Updated: 2020/12/14 19:02:06 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int count_line(char **env)
{
	int i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	return (i);
}

void	export_cmd(char *name,char **env)
{
	int i = 0;
	int line = count_line(env);
	printf("{%d}",line);
	env[line] = name;
	env[line+1] = NULL;
}
int main(int argc, char **argv,char **env)
{
	t_path path;
	t_key key;
	t_cmd cmd;
	// char *env_tmp[33];
	char *s;
	init(&path,&key,&cmd);
	path.env->fullenv = env;
	export_cmd("myvar=300",path.env->fullenv);
	// printf("\nHERE ; [%s]\n",search_env(path.env->fullenv,"PWD"));
	int i = 0;
	int line = count_line(env);
	// while (i < li)
	// {
	// 	puts(env[i]);
	// 	i++;
	// }
	
	// printf("{%d}",count_line(env));
	// cd_cmd("srcs",&path);
	get_directory(&path);
	// loop_shell(&cmd,&path);
	// getprogramme(&path,"ls");
	return (0);
}