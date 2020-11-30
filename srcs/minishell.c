/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamali <zjamali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 02:17:32 by helkhatr          #+#    #+#             */
/*   Updated: 2020/11/30 17:47:57 by zjamali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_env_variables(t_env_var *var_env, char **env)
{
	t_env_var *vr_env;
	int i;
	char *split;

	i = 0;
	vr_env = var_env;
	while(env[i])
	{
		if (vr_env = (t_env_var*)malloc(sizeof(t_env_var)));
			write(2,"allocation error",ft_strlen("allocation error"));
		split = ft_split(env[i],'=');
		vr_env->var_name = split[0];
		vr_env->var_value = split[1];
		vr_env = vr_env->next;
		i++;
	}	
	
}

int		main(int argc, char **argv, char **env)
{
	t_env_var *var_env;
	get_env_variables(var_env,env);

	while(var_env->next != NULL)
	{
		printf("%s\t",var_env->var_name);
		printf("%s\n",var_env->var_value);
		var_env = var_env->next;
	}
	//loop_shell();
	
	return (0);
}
