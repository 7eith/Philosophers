/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:57:15 by amonteli          #+#    #+#             */
/*   Updated: 2021/11/11 17:55:51 by amonteli         ###   ########lyon.fr   */
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

typedef struct s_global
{
	int			philo_count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			eat_count;
	int			has_die;
	long long	start;
	pthread_mutex_t		log_mtx;
}				t_global;

typedef struct s_philo
{
	t_global	*global;
	int			identifier;
	int			dead;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	r_fork;
}				t_philo;

/**
 * utilities.c
 */

int		ft_atoi(char *str);

#endif
