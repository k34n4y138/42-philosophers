/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime_monitors_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:50:10 by zmoumen           #+#    #+#             */
/*   Updated: 2023/03/10 15:33:08 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void	philoprocess(int id, t_args *pack)
{
	t_philo	philo;

	memset(&philo, 0, sizeof(t_philo));
	philo.id = id;
	philo.args = pack;
	pthread_create(&philo.ptid, NULL, philo_job, &philo);
	pthread_detach(philo.ptid);
	usleep(1000);
	monitor_philo(&philo);
}

static void	*philos_allate_monitor(void *vpack)
{
	t_args	*pack;
	int		i;

	pack = (t_args *)vpack;
	i = 0;
	while (i++ < pack->num_of_philos)
	{
		sem_wait(pack->allate);
		if (pack->willexit)
			while (1)
				usleep(10000);
	}
	pack->willexit = 1;
	sem_post(pack->philo_died);
	philos_reaper(pack, pack->num_of_philos, 0);
	return (NULL);
}

static void	*philo_death_monitor(void *vpack)
{
	t_args	*pack;

	pack = (t_args *)vpack;
	sem_wait(pack->philo_died);
	if (pack->willexit)
		return (NULL);
	pack->willexit = 1;
	sem_post(pack->allate);
	philos_reaper(pack, pack->num_of_philos, 1);
	return (NULL);
}

void	simulation_spinup(t_args *pack)
{
	int			id;
	pid_t		child;
	pthread_t	todetach;

	id = 0;
	pack->timeorigin = get_ms_time(0);
	while (id < pack->num_of_philos)
	{
		child = fork();
		if (!child)
		{
			philoprocess(id + 1, pack);
			exit(0);
		}
		else if (child < 0)
		{
			sem_wait(pack->printfsem);
			printf("FAILED TO CREATE CHILD PROCESSES!!\n");
			philos_reaper(pack, id + 1, 1);
		}
		pack->philopids[id++] = child;
	}
	pthread_create(&todetach, NULL, philo_death_monitor, pack);
	pthread_detach(todetach);
	philos_allate_monitor(pack);
}
