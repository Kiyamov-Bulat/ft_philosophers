#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

# include "../utils/utils.h"

# define PORTION_DEVIDER 10

/*
** === For each PHILO_TYPE its own definition ===
*/

typedef pthread_mutex_t		t_fork;

typedef pthread_mutex_t		t_locker;

typedef struct s_philo
{
	const size_t			id;
	const t_args			*args;
	t_fork					*forks[2];
	t_msec					last_meal;
	size_t					nmeals;
	t_locker				state;
	int						is_over;
}							t_philo;

int							philo_is_dead(t_philo *philo);
int							wait_philo_death(t_philo *philos);
int							print_philo_status(size_t ph_num, \
								const char *status);
int							start_act(t_philo *philo, \
								const char *msg, t_msec dur);

t_philo						*init_philos(const t_args *args, t_fork *forks);
int							destroy_philos(t_philo *philos);
t_fork						*init_forks(size_t forks_num);
int							grab_fork(t_fork **forks, size_t ph_id);
int							return_forks(t_fork **forks, size_t ph_id);
int							destroy_forks(t_fork *forks, \
								size_t forks_num);
int							pthread_lock(t_locker *locker);
int							pthread_unlock(t_locker *locker);
t_locker					*init_print_locker(void);
int							destroy_print_locker(void);

/*
** ==============================================
*/

#endif
