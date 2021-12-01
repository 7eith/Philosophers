/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:56:01 by amonteli          #+#    #+#             */
/*   Updated: 2021/12/01 01:33:24 by amonteli         ###   ########lyon.fr   */
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
		global->eat_count = -1;
	else
		global->eat_count = ft_atoi(args[5]);
	if (global->philo_count == 0 || global->time_to_die == 0 || global->time_to_eat == 0 || global->time_to_sleep == 0 || global->eat_count == 0)
		return (0);
	printf("[DEBUG] params=[{%d}, {%d}, {%d}, {%d}, {%d}]", global->philo_count, global->time_to_die, global->time_to_eat, global->time_to_sleep, global->eat_count);
	return (1);
}

void	ps_log(t_philo *philosopher, char *type)
{
	pthread_mutex_lock(&philosopher->global->log_mtx);
	printf("| %*lld | %.*d has %s\n", 4, get_time() - philosopher->global->start, philosopher->global->philo_count, philosopher->identifier, type);
	pthread_mutex_unlock(&philosopher->global->log_mtx);
}

void	eat(t_philo *philosopher)
{
	philosopher->eat = 0;
	if (philosopher->global->philo_count == 1)
	{
		usleep((philosopher->global->time_to_die) * 1000);
		ps_log(philosopher, A_DIE);
		philosopher->dead = 1;
		return ;
	}
	if (!philosopher->identifier % 2)
	{
		pthread_mutex_lock(philosopher->l_fork);

		// pthread_mutex_lock(&philosopher->r_fork);
		// pthread_mutex_lock(&philosopher->r_fork);

	}
	else
	{
		pthread_mutex_lock(&philosopher->r_fork);
	}
	ps_log(philosopher, A_EAT);
}

void	*launch_philo(void *data)
{
	t_philo *philosopher;

	philosopher = data;
	if (philosopher->identifier % 2)
		usleep(1500);
	while (!philosopher->dead)
	{
		// ps_log(philosopher, A_THINK);
		eat(philosopher);
	}
	// TODO: check if time to die < eat + sleep + think
	return (philosopher);
}

int	main(int args_count, char **args)
{
	t_global	global;
	t_philo		*philosophers;
	int			index;
	pthread_t	*threads;

	if (args_count < 5 || args_count > 6)
		return (errors("use ./philo <philos> <time_to_die> <time_to_eat> <time_to_sleep> [max_eat_phase]"));
	if (!parse_args(&global, args, args_count))
		return (errors("failed to parse"));
	printf("{%d}\n", global.philo_count);
	philosophers = malloc(sizeof(t_philo) * global.philo_count);
	if (!philosophers)
		return (-1);
	pthread_mutex_init(&global.log_mtx, NULL);
	index = 0;
	while (index < global.philo_count)
	{
		philosophers[index].global = &global;
		philosophers[index].identifier = index + 1;
		philosophers[index].dead = 0;
		philosophers[index].eat = 0;
		philosophers[index].max_eat = -1;
		pthread_mutex_init(&philosophers[index].r_fork, NULL);
		if (index != 0)
			philosophers[index].l_fork = &philosophers[index - 1].r_fork;
		index++;
	}
	philosophers[index - 1].l_fork = &philosophers[index - 1].r_fork;
	threads = malloc(sizeof(pthread_t) * global.philo_count);
	if (!threads)
		return (-1);
	index = 0;
	global.start = get_time();
	while (index < global.philo_count)
	{
		pthread_create(&threads[index], NULL, launch_philo, &philosophers[index]);
		index++;
	}
	index = 0;
	while (index < global.philo_count)
		pthread_join(threads[index++], NULL);
	return (1);
}
