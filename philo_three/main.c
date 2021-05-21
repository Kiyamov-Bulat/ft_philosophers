#include "philosophers.h"

static t_locker	*g_entry_point;

static void	*eat(void *raw_philo)
{
	t_philo			*philo;

	philo = (t_philo *)raw_philo;
	while (1)
	{
		pthread_lock(g_entry_point);
		grab_fork(&philo->forks, philo->id);
		pthread_unlock(g_entry_point);
		pthread_lock(philo->state);
		philo->last_meal = get_current_time_ms();
		pthread_unlock(philo->state);
		if (start_act(philo, "is eating", philo->args->eat_time))
		{
			return_forks(&philo->forks, philo->id);
			break ;
		}
		++philo->nmeals;
		return_forks(&philo->forks, philo->id);
		if (start_act(philo, "is sleeping", philo->args->sleep_time))
			break ;
		if (start_act(philo, "is thinking", 0))
			break ;
	}
	return (NULL);
}

static int	start_lunch(t_philo *philos)
{
	size_t			i;
	size_t			ph_num;
	pthread_t		thread_id;

	i = 0;
	ph_num = philos->args->ph_num;
	while (i < ph_num)
	{
		philos[i].pid = fork();
		if (philos[i].pid == -1)
			return (-1);
		if (philos[i].pid == 0)
		{
			pthread_create(&thread_id, NULL, check_philo_is_over, philos + i);
			eat(philos + i);
			pthread_detach(thread_id);
			return (0);
		}
		++i;
	}
	return (wait_philo_death(philos));
}

static int	init(t_philo **philos, t_fork **forks, t_args *parsed_args)
{
	if (init_print_locker())
		return (1);
	if (init_nwell_fed_storage())
		return (1);
	g_entry_point = pthread_locker_init(ENTRY_POINT_SEM_NAME, 1);
	if (g_entry_point == NULL)
		return (1);
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

static int	destroy(t_philo *philos, t_fork *forks)
{
	int	err;

	err = destroy_forks(forks, philos->args->ph_num);
	err |= destroy_philos(philos);
	err |= destroy_print_locker();
	err |= destroy_nwell_fed_storage();
	err |= pthread_locker_destroy(g_entry_point, ENTRY_POINT_SEM_NAME);
	return (err);
}

int	main(int argc, char *argv[])
{
	t_args			parsed_args;
	t_fork			*forks;
	t_philo			*philos;

	if (parse_args(argc, argv, &parsed_args))
		return (EXIT_FAILURE);
	if (init(&philos, &forks, &parsed_args))
		return (EXIT_FAILURE);
	if (start_lunch(philos) == -1)
	{
		destroy(philos, forks);
		return (EXIT_FAILURE);
	}
	if (destroy(philos, forks))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
