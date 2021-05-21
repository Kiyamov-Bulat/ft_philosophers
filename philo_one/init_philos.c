#include "philosophers.h"

t_philo	*init_philos(const t_args *args, t_fork *forks)
{
	size_t	i;
	t_philo	*philos;

	philos = (t_philo *)malloc(args->ph_num * sizeof(*philos));
	if (philos == NULL)
	{
		error("allocation error!\n");
		return (NULL);
	}
	i = 0;
	while (i < args->ph_num)
	{
		*(size_t *)&philos[i].id = i + 1;
		philos[i].args = args;
		philos[i].forks[0] = forks + i;
		philos[i].forks[1] = forks + (i + 1) % args->ph_num;
		philos[i].nmeals = 0;
		philos[i].is_over = 0;
		philos[i].last_meal = get_current_time_ms();
		if (pthread_mutex_init(&philos[i].state, NULL))
			return (NULL);
		i++;
	}
	return (philos);
}

int	destroy_philos(t_philo *philos)
{
	int		err;
	size_t	i;

	i = 0;
	err = 0;
	while (i < philos->args->ph_num)
	{
		err |= pthread_mutex_destroy(&philos[i].state);
		i++;
	}
	free(philos);
	return (err);
}
