/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 10:15:25 by helkhatr          #+#    #+#             */
/*   Updated: 2021/02/15 15:48:28 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atoi_long(char *str)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\r' || str[i] == '\f' || str[i] == '\n'
			|| str[i] == '\v' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1 * sign;
		i++;
	}
	while (str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}

void		print_err_exite(char *s)
{
	ft_putendl_fd("exit", 2);
	ft_putstr_fd("\e[1;31m exit ", 2);
	ft_putstr_fd(s, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

int			is_int(char *str)
{
	int		i;

	i = 0;
	while (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int			count_digit(char *str)
{
	int		i;
	int		c;

	i = 0;
	c = 1;
	while (str[i] == '0')
		i++;
	while (str[i])
	{
		c++;
		i++;
	}
	return (c);
}

char		*ft_strjoin_free(char *s1, char const *s2)
{
	char	*p;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	if (!s1)
		return (ft_strdup(s2));
	if (s1 && s2)
	{
		if (!(p = (char *)malloc(sizeof(char) * (ft_strlen(s1)
							+ ft_strlen(s2) + 1))))
			return (NULL);
		while (s1[j])
			p[i++] = s1[j++];
		while (s2[k])
			p[i++] = s2[k++];
		p[i] = '\0';
		return (p);
	}
	return (NULL);
}
