/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <diyanazizo13@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 11:51:16 by zdnaya            #+#    #+#             */
/*   Updated: 2020/12/16 22:35:45 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*freez(char **buff)
{
	if (buff != NULL && *buff != NULL)
	{
		free(*buff);
		*buff = NULL;
	}
	return (NULL);
}

static	int		ft_next(char **str, char **line, int r)
{
	char		*tmp;
	char		*endl;

	if (r == 0 && (*str == NULL || *str == (void *)0))
	{
		*line = ft_strdup("");
		return (0);
	}
	if ((endl = ft_strchr(*str, '\n')))
	{
		endl[0] = 0;
		*line = ft_strdup(*str);
		tmp = *str;
		*str = endl[1] ? ft_strdup(endl + 1) : freez(str);
		if (*str)
			free(tmp);
	}
	else if (*str && r == 0)
	{
		*line = *str;
		freez(str);
		return (0);
	}
	return (1);
}

int				get_next_line(int fd, char **line)
{
	char		*buff;
	int			r;
	char		*tmp;
	static char *str[2];

	buff = NULL;
	if (!(buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))) || fd < 0 ||
			line == NULL)
	{
		freez(&buff);
		return (-1);
	}
	while ((r = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[r] = '\0';
		tmp = str[1];
		str[1] = !str[1] ? ft_strdup(buff) : ft_strjoin(str[1], buff);
		ft_bzero(buff, BUFFER_SIZE + 1);
		if (tmp)
			free(tmp);
		if ((tmp = ft_strchr(str[1], '\n')))
			break ;
	}
	freez(&buff);
	return (r < 0 ? -1 : ft_next(&str[1], line, r));
}
