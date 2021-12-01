/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 01:52:05 by amonteli          #+#    #+#             */
/*   Updated: 2021/12/01 05:18:13 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse_args(t_global *global, char **args, int args_count)
{
	global->philo_count = ft_atoi(args[1]);
	global->time_to_die = ft_atoi(args[2]);
	global->time_to_eat = ft_atoi(args[3]);
	global->time_to_sleep = ft_atoi(args[4]);
	global->has_die = 0;
	if (args_count == 5)
		global->max_eat_count = -1;
	else
		global->max_eat_count = ft_atoi(args[5]);
	if (global->philo_count == 0 || global->time_to_die == 0 || global->time_to_eat == 0 || global->time_to_sleep == 0 || global->max_eat_count == 0)
		return (0);
	printf("[DEBUG] params=[{%d}, {%d}, {%d}, {%d}, {%d}]\n", global->philo_count, global->time_to_die, global->time_to_eat, global->time_to_sleep, global->max_eat_count);
	return (1);
}

int	init_philosophers(t_global *global, t_philo *philos)
{
	int		index;

	index = 0;
	while (index < global->philo_count)
	{
		philos[index].global = global;
		philos[index].identifier = index + 1;
		philos[index].dead = 0;
		philos[index].eat = 0;
		philos[index].max_eat = global->max_eat_count;
		philos[index].last_time_eat = 0;
		pthread_mutex_init(&philos[index].r_fork, NULL);
		if (index != 0)
			philos[index].l_fork = &philos[index - 1].r_fork;
		index++;
	}
	philos[0].l_fork = &philos[index - 1].r_fork;
	return (1);
}

int	main(int argc, char **args)
{
	t_global	global;
	t_philo		*philosophers;
	pthread_t	*threads;
	int			index;

	if (argc < 5 || argc > 6)
		return (errors("use ./philo <philos> <time_to_die> <time_to_eat> <time_to_sleep> [max_eat_phase]"));
	if (!parse_args(&global, args, argc))
		return (errors("failed to parse"));
	philosophers = malloc(sizeof(t_philo) * global.philo_count);
	pthread_mutex_init(&global.log_mtx, NULL);
	if (!philosophers || !init_philosophers(&global, philosophers))
		return (0);
	threads = malloc(sizeof(pthread_t) * global.philo_count);
	if (!threads)
		return (0);
	global.start = get_time();
	index = 0;
	while (index < global.philo_count)
	{
		pthread_create(&threads[index], NULL, launch_tasks, &philosophers[index]);
		usleep(1);
		index++;
	}
	index = 0;
	while (index < global.philo_count)
		pthread_join(threads[index++], NULL);
	return (1);
}
