/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:00:02 by amonteli          #+#    #+#             */
/*   Updated: 2021/11/10 20:35:49 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_integer(char *str)
{
	int		index;

	index = 0;
	while (str[index])
	{
		if (!(str[index] >= '0' && str[index] <= '9'))
			return (0);
		index++;
	}
	return (1);
}

int	ft_atoi(char *str)
{
	int		i;
	int		neg;
	long	number;

	neg = 1;
	i = 0;
	number = 0;
	if (!is_integer(str))
		return (0);
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '-' && (str[i + 1] > 47 && str[i + 1] < 58))
	{
		neg = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] > 47 && str[i] < 58)
	{
		number = number * 10 + (str[i] - 48);
		i++;
	}
	return (number * neg);
}
