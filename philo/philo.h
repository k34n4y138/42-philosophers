/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:40:56 by zmoumen           #+#    #+#             */
/*   Updated: 2023/02/14 18:29:49 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
#include <sys/_pthread/_pthread_mutex_t.h>
#include <sys/_pthread/_pthread_t.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
#include <time.h>

int	ft_atoi(char *str);

typedef struct s_args
{
	int num_of_philos;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int times_to_eat;

}       t_args;
/*
create->sleep-> wakeup and reach their fork
							|-> eat if two forks aquired
							|				^
							|->think till neighbor's fork is aquired -> die if last meal's timestamp exceed time_to_die
*/

typedef enum
{
	PHILO_NEW,
	PHILO_EATING,
	PHILO_SLEEPING,
	PHILO_THINKING,
	
} t_philostate;

typedef struct s_philo 
{
	t_args			*args;
	pthread_t		id;
	pthread_mutex_t	fork;
	int				times_ate;
	t_philostate	status;
	time_t			last_meal;
	struct s_philo	*neighbor;
}	t_philo;
#endif