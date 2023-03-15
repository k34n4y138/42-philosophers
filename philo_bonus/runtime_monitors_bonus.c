/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime_monitors_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:50:10 by zmoumen           #+#    #+#             */
/*   Updated: 2023/03/15 20:23:17 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	*monitor_philo(t_philo *vphilo)
{
	int			last_meal_informed;
	t_philo		*philo;
	pthread_t	detach;

	philo = (t_philo *)vphilo;
	last_meal_informed = 0;
	while (1)
	{
		if (g_philo_timesate(philo, 0) >= philo->args->times_to_eat
			&& !last_meal_informed)
			(!sem_post(philo->args->allate) && (last_meal_informed = 1));
		if (
			!philo_mealtimer(philo, 0, 0, 1))
		{
			announce_state(philo, "died", 1);
			sem_post(philo->args->philo_died);
			pthread_create(&detach, NULL, seppuku, philo);
			mssleep(1000);
		}
		usleep(800);
	}
	return (NULL);
}

static void	philoprocess(int id, t_args *pack)
{
	t_philo	philo;

	memset(&philo, 0, sizeof(t_philo));
	philo.id = id;
	philo.args = pack;
	simple_itoa(philo.innersemname, INNERSEMPRFX, id);
	sem_unlink(philo.innersemname);
	philo.meal_meta_sem = sem_open(philo.innersemname,
			O_CREAT | O_EXCL, S_IRWXU, 1);
	if (philo.meal_meta_sem == SEM_FAILED)
	{
		announce_state(&philo, "coudn't create needed semaphores!", 1);
		sem_post(pack->philo_died);
		exit(1);
	}
	sem_unlink(philo.innersemname);
	philo.last_meal = get_ms_time(0);
	pthread_create(&philo.ptid, NULL, philo_job, &philo);
	pthread_detach(philo.ptid);
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
		trap_till_exit(pack, 0);
	}
	trap_till_exit(pack, 1);
	sem_post(pack->philo_died);
	philos_reaper(pack, pack->num_of_philos, 0);
	return (NULL);
}

static void	*philo_death_monitor(void *vpack)
{
	t_args	*pack;

	pack = (t_args *)vpack;
	sem_wait(pack->philo_died);
	trap_till_exit(pack, 1);
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
			philoprocess(id + 1, pack);
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
	usleep(500);
	while (id--)
		sem_post(pack->startsim);
	philos_allate_monitor(pack);
}
