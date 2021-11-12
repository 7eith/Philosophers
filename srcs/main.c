/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:56:01 by amonteli          #+#    #+#             */
/*   Updated: 2021/11/12 19:21:03 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	errors(char *error)
{
	printf("Error: {%s}\n", error);
	return (0);
}

int get_time()
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	print_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->global->log_mtx);
	printf("\e[91m%lld \e[0m| Thread %d is sleeping 💤\n", get_time()
		- philo->global->start, philo->identifier);
	pthread_mutex_unlock(&philo->global->log_mtx);
	usleep(philo->global->time_to_sleep * 1000);
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

void	*launch_philo(void *data)
{
	t_philo *philosopher;

	philosopher = data;
	if (philosopher->identifier % 2)
		usleep(1500);
	print_sleep(philosopher);
	// TODO: check if time to die < eat + sleep + think
	return (philosopher);
}

int	main(int args_count, char **args)
{
	t_global	global;
	t_philo		*philosophers;
	int			index;
	pthread_t	*threads;

	index = 0;
	if (args_count < 5 || args_count > 6)
		return (errors("use ./philo <philos> <time_to_die> <time_to_eat> <time_to_sleep> [max_eat_phase]"));
	if (!parse_args(&global, args, args_count))
		return (errors("failed to parse"));
	philosophers = malloc(sizeof(t_philo) * global.philo_count);
	if (!philosophers)
		return (-1);
	pthread_mutex_init(&global.log_mtx, NULL);
	while (index < global.philo_count)
	{
		philosophers[index].global = &global;
		philosophers[index].identifier = index + 1;
		philosophers[index].dead = 0;
		pthread_mutex_init(&philosophers[index].r_fork, NULL);
		if (index != 0)
			philosophers[index].l_fork = &philosophers[index - 1].r_fork;
		index++;
	}
	philosophers[index].l_fork = &philosophers[index].r_fork;
	threads = malloc(sizeof(pthread_t) * global.philo_count);
	if (!threads)
		return (-1);
	index = 0;
	global.start = get_time();
	while (index < global.philo_count)
	{
		pthread_create(&threads[index], NULL, launch_philo, &philosophers[index]);
	}
	printf("time={%d}\n", get_time());
	return (1);
}
