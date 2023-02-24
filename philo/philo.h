/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:40:56 by zmoumen           #+#    #+#             */
/*   Updated: 2023/02/24 15:05:13 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

typedef struct s_args
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_to_eat;
	long			timeorigin;
	pthread_mutex_t	printmtx;
	pthread_mutex_t	simulationmtx;
	int				simulationcont;
}		t_args;

typedef enum e_philostate
{
	PHILO_NEW,
	PHILO_WILLEAT,
	PHILO_WILLSLEEP,
}		t_philostate;

typedef struct s_philo
{
	int				id;
	pthread_t		ptid;
	t_args			*args;
	t_philostate	state;
	pthread_mutex_t	fork;
	pthread_mutex_t	*fst_fork;
	pthread_mutex_t	*lst_fork;
	long			last_meal;
	pthread_mutex_t	meal_meta_mtx;
	int				times_ate;
	struct s_philo	*neighbor;
}	t_philo;

/*
	tools.c
*/
int		ft_atoi(char *str);
void	*ft_calloc(int size, int count);
/**/

/*
	spinup_routines.c
*/
int		initargs(char *av[], t_args *pack, int ac);
t_philo	*gen_philosophers(t_args	*args, int numofphilos);
void	spawn_philos(t_philo *philos, int numofphilos);
/**/

/*
	runtime_monitor.c
*/
int		gs_simulation_state(t_args *args, int setdone);
int		monitor_philos(t_philo *philo);
/**/

/*
	philo_runtime.c
*/
void	*philo_job(void	*vphilo);
/**/

/*
	events_helpers.c
*/
long	get_ms_time(long origin);
void	mssleep(long ms);
long	announce_state(t_philo *philo, char *state, int is_death);
int		g_philo_timesate(t_philo *philo);
long	philo_mealtimer(t_philo *philo, int set, long newval);
/**/

#endif