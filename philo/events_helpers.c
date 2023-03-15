/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:31:09 by zmoumen           #+#    #+#             */
/*   Updated: 2023/03/15 19:40:37 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

long	get_ms_time(long origin)
{
	struct timeval	tmv;

	gettimeofday(&tmv, NULL);
	return ((tmv.tv_sec * 1000 + tmv.tv_usec / 1000) - origin);
}

void	mssleep(long ms)
{
	long	tosleep;
	long	sleeptill;

	sleeptill = get_ms_time(0) + ms;
	tosleep = 3 * (ms / 4) * 1000;
	usleep(tosleep);
	tosleep = get_ms_time(0);
	while (tosleep < sleeptill)
	{
		usleep(100);
		tosleep = get_ms_time(0);
	}	
}

long	announce_state(t_philo *philo, char *state, int is_death)
{
	long	eventstamp;

	pthread_mutex_lock(&philo->args->printmtx);
	eventstamp = get_ms_time(0);
	if (gs_simulation_state(philo->args, 0) || is_death)
		printf("%ld %d %s\n",
			eventstamp - philo->args->timeorigin, philo->id, state);
	pthread_mutex_unlock(&philo->args->printmtx);
	return (eventstamp);
}

int	g_philo_timesate(t_philo *philo, int set)
{
	int	ret;

	pthread_mutex_lock(&philo->meal_meta_mtx);
	if (set)
		philo->times_ate++;
	ret = philo->times_ate;
	pthread_mutex_unlock(&philo->meal_meta_mtx);
	return (ret);
}

long	philo_mealtimer(t_philo *philo, int set, long newval)
{
	long	ret;

	pthread_mutex_lock(&philo->meal_meta_mtx);
	if (set)
	{
		philo->last_meal = newval;
	}
	ret = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_meta_mtx);
	return (ret);
}
