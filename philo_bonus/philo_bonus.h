/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:50:52 by zmoumen           #+#    #+#             */
/*   Updated: 2023/03/15 20:24:26 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# define PRINTFGUARD	"/philo_printfsem"
# define FORKSGUARD	"/philo_forksem"
# define ALLATESEM	"/philo_allatesem"
# define PHILODIEDSEM	"/philo_philodiedsem"
# define STARTSIM	"/philo_startsim"
# define INNERSEMPRFX "/philo_meta_"
# define ENDITALLSEM	"/philo_will_exit"
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
	sem_t			*startsim;
	sem_t			*enditallsem;
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
	char				innersemname[128];
	pthread_t			ptid;
	t_args				*args;
	t_philostate		state;
	long				last_meal;
	sem_t				*meal_meta_sem;
	long				times_ate;
}	t_philo;

/*
	tools
*/
int		ft_atoi(char *str);
void	*ft_calloc(int size, int count);
long	get_ms_time(long origin);
void	mssleep(long ms);
void	simple_itoa(char *bfr, char	*prefix, int num);

/*
	philo_runtime
*/
void	*philo_job(void	*vphilo);
long	announce_state(t_philo *philo, char *state, int is_death);
long	g_philo_timesate(t_philo *philo, int set);
long	philo_mealtimer(t_philo *philo, int set, long newval, int cmp);

/*
	cleanup
*/
void	unlink_semaphores(void);
void	philos_reaper(t_args *pack, int numofphilos, int exitstatus);
void	trap_till_exit(t_args	*pack, int set);
void	*seppuku(void *nulled);

/*
	runtime_monitors
*/
void	simulation_spinup(t_args *pack);
#endif