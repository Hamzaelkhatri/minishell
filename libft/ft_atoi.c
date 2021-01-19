/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr < helkhatr@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 03:40:41 by sqatim            #+#    #+#             */
/*   Updated: 2021/01/19 16:53:35 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	check(int counter, int sign, int result)
{
	if (counter > 19)
	{
		if (sign > 0)
			return (-3);
		else
			return (-3);
	}
	
	return (result * sign);
}

int			ft_atoi(const char *str)
{
	int i;
	int sign;
	int result;
	int counter;

	i = 0;
	sign = 1;
	result = 0;
	counter = 0;

	while (str[i] == ' ' || str[i] == '\r' || str[i] == '\f' || str[i] == '\n'
			|| str[i] == '\v' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1 * sign;
		i++;
	}
	while (str[i]=='0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
		counter++;
	}
	return (check(counter, sign, result));
}
