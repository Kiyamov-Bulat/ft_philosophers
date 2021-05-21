#include "philosophers.h"

static int	check_philo_state(t_philo *philo)
{
	pthread_lock(philo->state);
	if (philo_is_dead(philo))
	{
		philo->is_over = 1;
		pthread_unlock(philo->state);
		if (print_philo_status(philo->id, "died") == -1)
			return (-1);
		return (1);
	}
	pthread_unlock(philo->state);
	return (0);
}

static void	*wait_philos_well_fed(void *nphilos)
{
	size_t		nwell_fed;
	size_t		total_nwell_fed;
	t_locker	*current_nwell_fed;

	nwell_fed = 0;
	total_nwell_fed = *(size_t *)nphilos;
	current_nwell_fed = get_philos_nwell_fed();
	while (nwell_fed < total_nwell_fed)
	{
		sem_wait(current_nwell_fed);
		++nwell_fed;
	}
	kill(0, SIGINT);
	return (NULL);
}

void	*check_philo_is_over(void *raw_philo)
{
	t_philo		*philo;
	static int	already_reported = 0;

	philo = (t_philo *)raw_philo;
	while (1)
	{
		if (philo->nmeals >= philo->args->must_eat_n && !already_reported)
		{
			sem_post(get_philos_nwell_fed());
			already_reported = 1;
		}
		if (check_philo_state(philo))
		{
			exit(0);
			return (NULL);
		}
		usleep(2);
	}
	return ((void *)1);
}

int	wait_philo_death(t_philo *philos)
{
	size_t		ph_num;
	pthread_t	well_fed_waiter;

	ph_num = philos->args->ph_num;
	if (pthread_create(&well_fed_waiter, NULL, \
			wait_philos_well_fed, &ph_num))
		return (1);
	while (1)
	{
		if (waitpid(-1, NULL, WNOHANG) != 0)
			break ;
		usleep(5);
	}
	kill(0, SIGINT);
	pthread_detach(well_fed_waiter);
	return (0);
}
