/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 02:17:15 by amonteli          #+#    #+#             */
/*   Updated: 2021/12/03 19:55:42 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_alive(t_philo *philo)
{
	if (((get_time() - philo->global->start)
			- philo->last_time_eat) > philo->global->time_to_die)
	{
		if (!philo->global->has_die)
		{
			philo->global->has_die = 1;
			ps_log(philo, A_DIE);
			return (0);
		}
	}
	if (philo->global->has_die)
		return (0);
	return (1);
}

int	can_live(t_philo *philo)
{
	philo->now = (get_time() - philo->global->start) - philo->last_time_eat;
	if (!philo->has_eat && (philo->now
			+ philo->global->time_to_eat > philo->global->time_to_die))
	{
		if (philo->global->has_die)
			return (0);
		philo->global->has_die = 1;
		usleep((philo->global->time_to_die - philo->now) * 1000);
		ps_log(philo, A_DIE);
		return (0);
	}
	else if (philo->has_eat && (philo->now
			+ philo->global->time_to_sleep > philo->global->time_to_die))
	{
		if (philo->global->has_die)
			return (0);
		philo->global->has_die = 1;
		usleep((philo->global->time_to_die - philo->now) * 1000);
		ps_log(philo, A_DIE);
		return (0);
	}
	return (1);
}

void	sleep_task(t_philo *philo)
{
	ps_log(philo, A_SLEEP);
	if (!can_live(philo))
		return ;
	usleep(philo->global->time_to_sleep * 1000);
	if (philo->global->has_die)
		return ;
	ps_log(philo, A_THINK);
}

void	eat_task(t_philo *philo)
{
	if (philo->global->philo_count == 1)
		unsufissent_forks(philo);
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&philo->r_fork);
	if (!is_alive(philo))
	{
		pthread_mutex_unlock(&philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	ps_log(philo, A_TAKE);
	ps_log(philo, A_TAKE);
	ps_log(philo, A_EAT);
	if (!can_live(philo))
	{
		pthread_mutex_unlock(&philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	usleep(philo->global->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	philo->eat++;
	philo->has_eat = 1;
	philo->last_time_eat = (get_time() - philo->global->start);
}

void	*launch_tasks(void *data)
{
	t_philo		*philo;

	philo = data;
	while (philo->global->max_eat_count == -1 || philo->eat <= philo->max_eat)
	{
		philo->has_eat = 0;
		eat_task(philo);
		if (philo->global->has_die)
			return (0);
		sleep_task(philo);
		if (philo->global->has_die)
			return (0);
	}
	return (philo);
}
