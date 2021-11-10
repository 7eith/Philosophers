/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:56:01 by amonteli          #+#    #+#             */
/*   Updated: 2021/11/10 20:42:14 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	errors(char *error)
{
	printf("Error: {%s}\n", error);
	return (0);
}

int	parse_args(t_global *global, char **args, int args_count)
{
	global->philo_count = ft_atoi(args[1]);
	global->time_to_die = ft_atoi(args[2]);
	global->time_to_eat = ft_atoi(args[3]);
	global->time_to_sleep = ft_atoi(args[4]);
	global->has_die = 0;

	if (args_count == 5)
		global->eat_count = -1;
	else
		global->eat_count = ft_atoi(args[5]);
	if (global->philo_count == 0 || global->time_to_die == 0 || global->time_to_eat == 0 || global->time_to_sleep == 0 || global->eat_count == 0)
		return (0);
	printf("params=[{%d}, {%d}, {%d}, {%d}, {%d}]", global->philo_count, global->time_to_die, global->time_to_eat, global->time_to_sleep, global->eat_count);
	return (1);
}

int	init(t_global *global)
{

}

int	main(int args_count, char **args)
{
	t_global	global;
	t_philo		*philosophers;
	int			index;

	index = 0;
	if (args_count < 5 || args_count > 6)
		return (errors("use ./philo <philos> <time_to_die> <time_to_eat> <time_to_sleep> [max_eat_phase]"));
	if (!parse_args(&global, args, args_count))
		return (errors("failed to parse"));
	philosophers = malloc(sizeof(t_philo) * global.philo_count);
	while (index < global.philo_count)
	{
		philosophers[index].global = &global;
		philosophers[index].identifier = index;
		philosophers[index].dead = 0;
	}
	return (1);
}
