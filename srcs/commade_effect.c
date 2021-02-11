/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commade_effect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 10:32:06 by helkhatr          #+#    #+#             */
/*   Updated: 2021/02/11 17:11:33 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		commande_effect(t_list_cmd *lst, t_path *path)
{
	while (lst)
	{
		g_var2 = 1;
		if (lstsize(lst) > 1)
			pipes_cmd(path, lst);
		else
			get_cmd_(lst->command->s_left->l_element->cmd, path, lst->command);
		lst = lst->next;
	}
	g_var2 = 0;
	return (0);
}
