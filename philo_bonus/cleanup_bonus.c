/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:11:24 by zmoumen           #+#    #+#             */
/*   Updated: 2023/03/05 17:57:08 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void	unlink_semaphores(void)
{
	sem_unlink(PRINTFGUARD);
	sem_unlink(FORKSGUARD);
	sem_unlink(ALLATESEM);
	sem_unlink(PHILODIEDSEM);
}

void	philos_reaper(t_args *pack, int numofphilos, int exitstatus)
{
	int	i;
	int	ret;

	i = 0;
	while (i < numofphilos)
	{
		kill(pack->philopids[i], SIGINT);
		waitpid(pack->philopids[i], &ret, 0);
		i++;
	}
	sem_close(pack->allate);
	sem_close(pack->forks);
	sem_close(pack->philo_died);
	sem_close(pack->printfsem);
	unlink_semaphores();
	exit(exitstatus);
}

void	*seppuku(void *nulled)
{
	(void)nulled;
	mssleep(10);
	exit(126);
}
