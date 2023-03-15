/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:35:49 by zmoumen           #+#    #+#             */
/*   Updated: 2023/03/15 19:29:13 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	gs_simulation_state(t_args *args, int setdone)
{
	int	ret;

	pthread_mutex_lock(&args->simulationmtx);
	if (setdone)
		args->simulationcont = 0;
	ret = args->simulationcont;
	pthread_mutex_unlock(&args->simulationmtx);
	return (ret);
}

int	check_philo_died(t_philo *philo)
{
	if (get_ms_time(philo_mealtimer(philo, 0, 0)) > philo->args->time_to_die)
		return (1);
	return (0);
}

int	monitor_philos(t_philo *philo)
{
	int	philos_ate;

	while (philo->args->simulationcont)
	{
		if (philo->id == 1)
			philos_ate = 0;
		if (g_philo_timesate(philo, 0) >= philo->args->times_to_eat)
			philos_ate++;
		if (philos_ate == philo->args->num_of_philos)
		{
			gs_simulation_state(philo->args, 1);
			return (0);
		}
		if (check_philo_died(philo))
		{
			gs_simulation_state(philo->args, 1);
			announce_state(philo, "died", 1);
			return (1);
		}
		philo = philo->neighbor;
		usleep(100);
	}
	return (0);
}
