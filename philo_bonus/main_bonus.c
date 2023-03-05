/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:50:17 by zmoumen           #+#    #+#             */
/*   Updated: 2023/03/05 18:27:22 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <sys/semaphore.h>

int	initargs(char *av[], t_args *pack, int ac)
{
	memset(pack, 0, sizeof(t_args));
	pack->num_of_philos = ft_atoi(av[1]);
	pack->time_to_die = ft_atoi(av[2]);
	pack->time_to_eat = ft_atoi(av[3]);
	pack->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		pack->times_to_eat = ft_atoi(av[5]);
	else
		pack->times_to_eat = 2147483647;
	if (pack->num_of_philos < 1 || pack->num_of_philos > MAXPHILOS
		|| pack->time_to_die < 1 || pack->time_to_eat < 1
		|| pack->time_to_sleep < 1 || pack->times_to_eat < 1)
		return (1);
	unlink_semaphores();
	pack->forks = sem_open(FORKSGUARD, O_CREAT | O_EXCL,
			S_IRWXU, pack->num_of_philos);
	pack->printfsem = sem_open(PRINTFGUARD, O_CREAT | O_EXCL, S_IRWXU, 1);
	pack->allate = sem_open(ALLATESEM, O_CREAT | O_EXCL, S_IRWXU, 0);
	pack->philo_died = sem_open(PHILODIEDSEM, O_CREAT | O_EXCL, S_IRWXU, 0);
	if (pack->printfsem == SEM_FAILED || pack->forks == SEM_FAILED
		|| pack->allate == SEM_FAILED || pack->philo_died == SEM_FAILED)
		exit(printf("COULND'T CREATE NEEDED SEMAPHORES!\n"));
	return (0);
}

int	main(int ac, char **av)
{
	t_args		pack;

	if ((ac != 5 && ac != 6)
		|| initargs(av, &pack, ac))
	{
		printf("%s: USAGE: \n \
		Values must be positive integers, timestamps are in milliseconde \
		Required: number_of_philosophers (max is %d), time_to_die, time_to_eat, time_to_sleep \n \
		Opt: [number_of_times_each_philosopher_must_eat]\n", av[0], MAXPHILOS);
		return (ac - 1);
	}
	simulation_spinup(&pack);
	return (0);
}
