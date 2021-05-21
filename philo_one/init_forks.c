#include "philosophers.h"

t_fork	*init_forks(size_t forks_num)
{
	size_t	i;
	t_fork	*forks;

	forks = (t_fork *)ft_calloc(forks_num, sizeof(*forks));
	if (forks == NULL)
	{
		error("allocation error!\n");
		return (NULL);
	}
	i = 0;
	while (i < forks_num)
	{
		if (pthread_mutex_init(forks + i, NULL))
		{
			destroy_forks(forks, i);
			error("pthread_mutex_init error!\n");
			return (NULL);
		}
		i++;
	}
	return (forks);
}

int	grab_fork(t_fork *forks[2], size_t ph_id)
{
	int	err;

	err = pthread_lock(*(forks + !(ph_id % 2)));
	err |= pthread_lock(*(forks + ph_id % 2));
	return (err);
}

int	return_forks(t_fork *forks[2], size_t ph_id)
{
	int	err;

	err = pthread_unlock(*(forks + !(ph_id % 2)));
	err |= pthread_unlock(*(forks + ph_id % 2));
	return (err);
}

int	destroy_forks(t_fork *forks, size_t forks_num)
{
	size_t	i;

	i = 0;
	while (i < forks_num)
		pthread_mutex_destroy(forks + i++);
	free(forks);
	return (0);
}
