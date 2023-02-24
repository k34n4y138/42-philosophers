/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spinup_routines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:22:27 by zmoumen           #+#    #+#             */
/*   Updated: 2023/02/24 14:58:17 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
#include <unistd.h>

int	initargs(char *av[], t_args *pack, int ac)
{
	if (ac < 5)
		return (1);
	memset(pack, 0, sizeof(t_args));
	pack->num_of_philos = ft_atoi(av[1]);
	pack->time_to_die = ft_atoi(av[2]);
	pack->time_to_eat = ft_atoi(av[3]);
	pack->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		pack->times_to_eat = ft_atoi(av[5]);
	else
		pack->times_to_eat = 2147483647;
	if (pack->num_of_philos < 1
		|| pack->time_to_die < 1 || pack->time_to_eat < 1
		|| pack->time_to_sleep < 1 || pack->times_to_eat < 1)
		return (1);
	pthread_mutex_init(&pack->printmtx, NULL);
	pthread_mutex_init(&pack->simulationmtx, NULL);
	pack->simulationcont = 1;
	return (0);
}

t_philo	*gen_philosophers(t_args	*args, int numofphilos)
{
	t_philo	*philos;
	int		traverse;

	philos = ft_calloc(numofphilos, sizeof(t_philo));
	traverse = 0;
	while (philos && traverse < numofphilos)
	{
		philos[traverse].id = traverse + 1;
		philos[traverse].args = args;
		if (traverse == numofphilos - 1)
			philos[traverse].neighbor = philos;
		else
			philos[traverse].neighbor = philos + traverse + 1;
		pthread_mutex_init(&philos[traverse].fork, NULL);
		pthread_mutex_init(&philos[traverse].meal_meta_mtx, NULL);
		traverse++;
	}
	return (philos);
}

void	spawn_philos(t_philo *philos, int numofphilos)
{
	philos->args->timeorigin = get_ms_time(0);
	while (numofphilos--)
	{
		pthread_create(&philos->ptid, NULL, philo_job, philos);
		philos = philos->neighbor;
	}
	usleep(100);
}
