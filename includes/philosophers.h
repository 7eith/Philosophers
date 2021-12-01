/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:57:15 by amonteli          #+#    #+#             */
/*   Updated: 2021/12/01 01:32:59 by amonteli         ###   ########lyon.fr   */
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

# define A_EAT "EAT"
# define A_TAKE "TAKE"
# define A_SLEEP "SLEEP"
# define A_THINK "THINK"
# define A_DIE "died"

typedef struct s_global
{
	int					philo_count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					eat_count;
	int					has_die;
	long long			start;
	pthread_mutex_t		log_mtx;
}						t_global;

typedef struct s_philo
{
	t_global			*global;
	int					identifier;
	int					dead;
	int					last_time_eat;
	int					eat;
	int					max_eat;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		r_fork;
}				t_philo;

/**
 * utilities.c
 */

int		ft_atoi(char *str);
int		errors(char *error);
int		get_time(void);
int		is_integer(char *str);

#endif
