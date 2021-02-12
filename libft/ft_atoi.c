/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 10:24:26 by sqatim            #+#    #+#             */
/*   Updated: 2021/02/12 10:27:53 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(int counter, int sign, int result)
{
	if (counter > 19)
	{
		if (sign > 0)
			return (-1);
		else
			return (0);
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
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
		counter++;
	}
	return (check(counter, sign, result));
}
