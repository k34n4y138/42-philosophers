/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:40:43 by zmoumen           #+#    #+#             */
/*   Updated: 2023/02/24 15:05:52 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

void	winddown_philos(t_philo *philos, int numofphilos)
{
	while (numofphilos--)
	{
		pthread_join(philos->ptid, NULL);
		philos = philos->neighbor;
	}
}

void	app_exit_cleanup(t_philo *philos, int numofphilos)
{
	pthread_mutex_destroy(&philos->args->printmtx);
	pthread_mutex_destroy(&philos->args->simulationmtx);
	while (numofphilos--)
	{
		pthread_mutex_destroy(&philos->fork);
		pthread_mutex_destroy(&philos->meal_meta_mtx);
		philos = philos->neighbor;
	}
}

int	main(int ac, char **av)
{
	t_args	pack;
	t_philo	*philos;

	if ((ac != 5 && ac != 6)
		|| initargs(av, &pack, ac))
	{
		printf("%s: USAGE: \n \
		Values must be positive integers, timestamps are in milliseconde \
		Required: number_of_philosophers, time_to_die, time_to_eat, time_to_sleep \n \
		Optional: [number_of_times_each_philosopher_must_eat]\n", av[0]);
		return (ac - 1);
	}
	philos = gen_philosophers(&pack, pack.num_of_philos);
	spawn_philos(philos, pack.num_of_philos);
	monitor_philos(philos);
	winddown_philos(philos, pack.num_of_philos);
	free(philos);
	philos = NULL;
	return (0);
}
