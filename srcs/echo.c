/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr < helkhatr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:02:30 by zjamali           #+#    #+#             */
/*   Updated: 2021/01/19 11:29:17 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char **delete_quote(char **line)
{
	int i;
	int j;
	int index;
	char wich;

	i = 0;
	while (line[i])
	{
		j = 0;
		index = 0;
		while (line[i][j])
		{
			while (line[i][j] != 34 && line[i][j] != 39 && line[i][j])
				line[i][index++] = line[i][j++];
			if ((line[i][j] == 34 || line[i][j] == 39) && line[i][j])
			{
				wich = (line[i][j] == 34) ? 34 : 39;
				j++;
				while (line[i][j] != wich && line[i][j])
					line[i][index++] = line[i][j++];
				if (line[i][j] == '\0')
					line[i][index] = '\0';
				else
					j++;
			}
			if (line[i][j] == '\0')
				line[i][index] = '\0';
		}
		i++;
	}
	return (line);
}

bool check_quote(char *line)
{
	int i;
	int check;
	char wich;

	check = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			wich = (line[i] == 34) ? 34 : 39;
			i++;
			check = 0;
			while (line[i])
			{
				if (line[i] == wich)
				{
					check = 1;
					break;
				}
				i++;
			}
			if (check != 1)
				return (false);
		}
		if (line[i])
			i++;
	}
	return (true);
}

void ft_nhaydo_nl(char **tab)
{
	int count;
	int len;

	count = ft_2strlen(tab);
	len = ft_strlen(tab[count - 1]);
	tab[count - 1][len - 1] = '\0';
}

void echo(char *line, t_path *path, int ret)
{
	int i;
	char **tab;

	i = 1;
	if(line == NULL && !ret)
		ft_putendl_fd("",1);
	else
	if (check_quote(line))
	{
		tab = ft_space_split(line);
		tab = delete_quote(tab);
		{
			if (tab[1] == 0)
				path->key->cntrd = 1;
			else
			{
				// puts("HELLO");
				if (ft_strnstr(tab[1], "-n", 2) || ft_strnstr(tab[1], "-n\n", 3))
				{
					ft_nhaydo_nl(tab);
					i++;
				}
				while (i < ft_2strlen(tab))
				{
					ft_putstr_fd(tab[i++], 1);
						if (i < ft_2strlen(tab))
							write(1, " ", 1);
					}
				}
			}
		}
		else
		{
			ft_putstr_fd("check quotes", 1);
			exit(0);
		}
}
