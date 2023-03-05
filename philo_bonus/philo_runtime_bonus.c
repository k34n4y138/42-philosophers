/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_runtime_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:22:33 by zmoumen           #+#    #+#             */
/*   Updated: 2023/03/05 18:50:53 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdio.h>

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
	philo->last_meal = announce_state(philo, "is eating", 0);
	mssleep(philo->args->time_to_eat);
	philo->times_ate++;
	sem_post(philo->args->forks);
	sem_post(philo->args->forks);
	philo->state = PHILO_WILLSLEEP;
}

void	*philo_job(void	*vphilo)
{
	t_philo	*philo;

	philo = (t_philo *)vphilo;
	announce_state(philo, "is thinking", 0);
	if (philo->id % 2)
		philo->state = PHILO_WILLEAT;
	else
		philo->state = PHILO_WILLSLEEP;
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

int	check_philo_died(t_philo *philo)
{
	if (get_ms_time(philo->last_meal) > philo->args->time_to_die)
		return (1);
	return (0);
}

void	*monitor_philo(t_philo *vphilo)
{
	int			last_meal_informed;
	t_philo		*philo;
	pthread_t	detach;

	philo = (t_philo *)vphilo;
	last_meal_informed = 0;
	philo->last_meal = get_ms_time(0);
	while (1)
	{
		if (philo->times_ate >= philo->args->times_to_eat
			&& !last_meal_informed)
		{
			sem_post(philo->args->allate);
			last_meal_informed++;
		}
		if (check_philo_died(philo))
		{
			pthread_create(&detach, NULL, seppuku, NULL);
			announce_state(philo, "died", 1);
			sem_post(philo->args->philo_died);
		}
		usleep(100);
	}
	return (NULL);
}
