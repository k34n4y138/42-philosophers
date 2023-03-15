/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_runtime_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:22:33 by zmoumen           #+#    #+#             */
/*   Updated: 2023/03/15 20:24:07 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdio.h>
#include <unistd.h>

/*
	https://github.com/google/sanitizers/issues/1384
	-fsanitize=thread produces false positives that can 
		only be suppressed by using mutexes
*/

long	g_philo_timesate(t_philo *philo, int set)
{
	long	ret;

	sem_wait(philo->meal_meta_sem);
	if (set)
		philo->times_ate++;
	ret = philo->times_ate;
	sem_post(philo->meal_meta_sem);
	return (ret);
}

long	philo_mealtimer(t_philo *philo, int set, long newval, int cmp)
{
	long	ret;

	ret = 0;
	sem_wait(philo->meal_meta_sem);
	if (set)
		philo->last_meal = newval;
	else if (cmp && get_ms_time(philo->last_meal) >= philo->args->time_to_die)
		return (0);
	ret = philo->last_meal;
	sem_post(philo->meal_meta_sem);
	return (ret);
}

long	announce_state(t_philo *philo, char *state, int is_death)
{
	long	eventstamp;

	sem_wait(philo->args->printfsem);
	eventstamp = get_ms_time(0);
	printf("%ld %d %s\n",
		eventstamp - philo->args->timeorigin, philo->id, state);
	if (!is_death)
		sem_post(philo->args->printfsem);
	return (eventstamp);
}

void	philo_eat(t_philo *philo)
{
	announce_state(philo, "is thinking", 0);
	sem_wait(philo->args->forks);
	announce_state(philo, "has taken a fork", 0);
	sem_wait(philo->args->forks);
	announce_state(philo, "has taken a fork", 0);
	philo_mealtimer(philo, 1,
		announce_state(philo, "is eating", 0), 0);
	mssleep(philo->args->time_to_eat);
	sem_post(philo->args->forks);
	sem_post(philo->args->forks);
	g_philo_timesate(philo, 1);
	philo->state = PHILO_WILLSLEEP;
}

void	*philo_job(void	*vphilo)
{
	t_philo	*philo;

	philo = (t_philo *)vphilo;
	if (philo->id % 2)
		philo->state = PHILO_WILLEAT;
	else
		philo->state = PHILO_WILLSLEEP;
	sem_wait(philo->args->startsim);
	while (1)
	{
		if (philo->state == PHILO_WILLEAT)
			philo_eat(philo);
		else if (philo->state == PHILO_WILLSLEEP)
		{
			announce_state(philo, "is sleeping", 0);
			mssleep(philo->args->time_to_sleep);
			philo->state = PHILO_WILLEAT;
		}
	}
	return (philo);
}
