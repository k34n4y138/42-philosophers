/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:50:52 by zmoumen           #+#    #+#             */
/*   Updated: 2023/03/05 17:56:56 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# define PRINTFGUARD	"/printfsem"
# define FORKSGUARD	"/forksem"
# define ALLATESEM	"/allatesem"
# define PHILODIEDSEM	"/philodiedsem"
# define MAXPHILOS	6942

typedef struct s_args
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long			times_to_eat;
	long			timeorigin;
	int				willexit;
	pid_t			philopids[MAXPHILOS];
	sem_t			*printfsem;
	sem_t			*allate;
	sem_t			*forks;
	sem_t			*philo_died;
}		t_args;

typedef enum e_philostate
{
	PHILO_NEW,
	PHILO_WILLEAT,
	PHILO_WILLSLEEP,
}		t_philostate;

typedef struct s_philo
{
	int					id;
	pid_t				pid;
	pthread_t			ptid;
	t_args				*args;
	t_philostate		state;
	long				last_meal;
	pthread_mutex_t		meal_meta_mtx;
	long				times_ate;
}	t_philo;

/*
	tools.c
*/
int		ft_atoi(char *str);
void	*ft_calloc(int size, int count);
long	get_ms_time(long origin);
void	mssleep(long ms);
//

/*
	philo_runtime.c
*/
void	*monitor_philo(t_philo *vphilo);
void	*philo_job(void	*vphilo);

void	unlink_semaphores(void);
void	philos_reaper(t_args *pack, int numofphilos, int exitstatus);

void	simulation_spinup(t_args *pack);
void	*seppuku(void *nulled);
#endif