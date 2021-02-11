/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:43:16 by helkhatr          #+#    #+#             */
/*   Updated: 2021/02/11 18:51:04 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_strdup_extra(char **str)
{
	char	**ptr;
	int		i;

	if (!(ptr = malloc(sizeof(char *) * count_line(str))))
		return (NULL);
	i = 0;
	while (str[i + 1])
	{
		ptr[i] = ft_strdup(str[i]);
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}

void	ft_sortstr(char **str)
{
	int		i;
	int		j;
	int		count;
	char	*tmp;
	char	*temp;

	i = 0;
	count = count_line(str);
	while (i <= count && str[i])
	{
		j = i;
		while (++j <= count && str[j])
		{
			if (ft_memcmp(str[i], str[j], ft_strlen(str[j])) > 0)
			{
				temp = (str[i]);
				tmp = str[i];
				str[i] = (str[j]);
				tmp = str[j];
				str[j] = (temp);
			}
		}
		i++;
	}
}

void	execute_export(t_path *path)
{
	char	**tmp;

	tmp = path->env->fullenv;
	ft_sortstr(tmp);
	show_export(tmp);
	path->dollar = 0;
}

void	execute_export_(t_path *path, t_command *l_cmd)
{
	while (l_cmd->s_left->right)
	{
		if (!export_cmd(l_cmd->s_left->right->l_element->argument, path))
			break ;
		l_cmd->s_left->right = l_cmd->s_left->right->right;
	}
}
