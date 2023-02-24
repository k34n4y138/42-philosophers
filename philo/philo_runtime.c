/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_runtime.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:30:12 by zmoumen           #+#    #+#             */
/*   Updated: 2023/02/24 15:02:34 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static void	philo_eat(t_philo *philo)
{
	announce_state(philo, "is thinking", 0);
	pthread_mutex_lock(philo->fst_fork);
	announce_state(philo, "has taken a fork", 0);
	if (philo->fst_fork == philo->lst_fork)
	{
		while (gs_simulation_state(philo->args, 0))
			usleep(10);
		pthread_mutex_unlock(philo->fst_fork);
		return ;
	}
	pthread_mutex_lock(philo->lst_fork);
	announce_state(philo, "has taken a fork", 0);
	philo_mealtimer(philo, 1, announce_state(philo, "is eating", 0));
	mssleep(philo->args->time_to_eat);
	pthread_mutex_unlock(philo->fst_fork);
	pthread_mutex_unlock(philo->lst_fork);
	philo->state = PHILO_WILLSLEEP;
}

static void	philo_sleep(t_philo *philo)
{
	announce_state(philo, "is sleeping", 0);
	mssleep(philo->args->time_to_sleep);
	philo->state = PHILO_WILLEAT;
}

void	*philo_job(void	*vphilo)
{
	t_philo	*philo;

	philo = (t_philo *)vphilo;
	philo->last_meal = get_ms_time(0);
	if (philo->id % 2)
	{
		philo->fst_fork = &philo->neighbor->fork;
		philo->lst_fork = &philo->fork;
		philo->state = PHILO_WILLEAT;
	}
	else
	{
		philo->fst_fork = &philo->fork;
		philo->lst_fork = &philo->neighbor->fork;
		philo->state = PHILO_WILLSLEEP;
	}
	while (gs_simulation_state(philo->args, 0))
	{
		if (philo->state == PHILO_WILLEAT)
			philo_eat(philo);
		else if (philo->state == PHILO_WILLSLEEP)
			philo_sleep(philo);
	}
	return (philo);
}
