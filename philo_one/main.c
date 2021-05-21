#include "philosophers.h"

static void	*eat(void *raw_philo)
{
	t_philo			*philo;

	philo = (t_philo *)raw_philo;
	while (1)
	{
		grab_fork(philo->forks, philo->id);
		pthread_lock(&philo->state);
		philo->last_meal = get_current_time_ms();
		pthread_unlock(&philo->state);
		if (start_act(philo, "is eating", philo->args->eat_time))
		{
			return_forks(philo->forks, philo->id);
			break ;
		}
		++philo->nmeals;
		return_forks(philo->forks, philo->id);
		if (start_act(philo, "is sleeping", philo->args->sleep_time))
			break ;
		if (start_act(philo, "is thinking", 0))
			break ;
	}
	return (NULL);
}

static pthread_t	*start_lunch(t_philo *philos)
{
	size_t			i;
	size_t			ph_num;
	pthread_t		*thread_ids;

	i = 0;
	ph_num = philos->args->ph_num;
	thread_ids = (pthread_t *)ft_calloc(ph_num, sizeof(*thread_ids));
	if (thread_ids == NULL)
	{
		error("allocation error!\n");
		return (NULL);
	}
	while (i < ph_num)
	{
		if (pthread_create(thread_ids + i, NULL, eat, philos + i))
		{
			destroy_threads(thread_ids, i);
			return (NULL);
		}
		++i;
	}
	return (thread_ids);
}

static int	init(t_philo **philos, t_fork **forks, t_args *parsed_args)
{
	*forks = init_forks(parsed_args->ph_num);
	if (*forks == NULL)
		return (1);
	*philos = init_philos(parsed_args, *forks);
	if (*philos == NULL)
	{
		destroy_forks(*forks, parsed_args->ph_num);
		return (1);
	}
	if (init_start_of_simulation())
		return (1);
	return (0);
}

static int	destroy(pthread_t *thread_ids, t_philo *philos, t_fork *forks)
{
	int	err;

	if (destroy_threads(thread_ids, philos->args->ph_num))
		return (1);
	err = destroy_forks(forks, philos->args->ph_num);
	err |= destroy_philos(philos);
	return (err);
}

int	main(int argc, char *argv[])
{
	t_args			parsed_args;
	t_fork			*forks;
	t_philo			*philos;
	pthread_t		*thread_ids;

	if (parse_args(argc, argv, &parsed_args))
		return (EXIT_FAILURE);
	if (init(&philos, &forks, &parsed_args))
		return (EXIT_FAILURE);
	thread_ids = start_lunch(philos);
	if (thread_ids == NULL)
		return (EXIT_FAILURE);
	wait_philo_death(philos);
	if (destroy(thread_ids, philos, forks))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
