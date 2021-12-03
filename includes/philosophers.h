/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:57:15 by amonteli          #+#    #+#             */
/*   Updated: 2021/12/03 19:57:26 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

# define A_EAT "is eating"
# define A_TAKE "has taken a fork"
# define A_SLEEP "is sleeping"
# define A_THINK "is thinking"
# define A_DIE "died"
# define E_INVALID_ARGS "use ./philo <philos> \
	<time_to_die> <time_to_eat> <time_to_sleep> [max_eat_phase]"

typedef struct s_global
{
	int					philo_count;
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	unsigned long		time_to_sleep;
	int					max_eat_count;

	int					has_die;
	unsigned long		start;
	pthread_mutex_t		log_mtx;
}						t_global;

typedef struct s_philo
{
	t_global			*global;
	int					identifier;
	int					dead;
	unsigned long		last_time_eat;
	unsigned long		now;
	int					eat;
	int					has_eat;
	int					max_eat;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		r_fork;
}				t_philo;

/**
 * main.c
 */

void			ps_log(t_philo *philo, char *type);

/**
 * utilities.c
 */

int				ft_atoi(char *str);
int				errors(char *error);
unsigned long	get_time(void);
int				is_integer(char *str);
void			unsufissent_forks(t_philo *philo);

/**
 * tasks.c
 */

int				is_alive(t_philo *philo);
int				can_live(t_philo *philo);
void			sleep_task(t_philo *philo);
void			eat_task(t_philo *philo);
void			*launch_tasks(void *data);

#endif
