#include "philosophers.h"

t_fork	*init_forks(size_t forks_num)
{
	t_fork	*forks;

	forks = pthread_locker_init(FORK_SEM_NAME, forks_num);
	return (forks);
}

int	grab_fork(t_fork **forks, size_t ph_id)
{
	int	err;

	(void)ph_id;
	err = sem_wait(*forks);
	err |= sem_wait(*forks);
	return (err);
}

int	return_forks(t_fork **forks, size_t ph_id)
{
	int	err;

	(void)ph_id;
	err = sem_post(*forks);
	err |= sem_post(*forks);
	return (err);
}

int	destroy_forks(t_fork *forks, size_t forks_num)
{
	(void)forks_num;
	return (pthread_locker_destroy(forks, FORK_SEM_NAME));
}
