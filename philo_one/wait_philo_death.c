#include "philosophers.h"

static	void	set_philos_states_as_over(t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < philos->args->ph_num)
		philos[i++].is_over = 1;
}

static	int	check_philo_state(t_philo *philo)
{
	pthread_lock(&philo->state);
	if (philo_is_dead(philo))
	{
		philo->is_over = 1;
		pthread_unlock(&philo->state);
		if (print_philo_status(philo->id, "died") == -1)
			return (-1);
		return (1);
	}
	pthread_unlock(&philo->state);
	return (0);
}

int	wait_philo_death(t_philo *philos)
{
	size_t	i;
	size_t	num;
	size_t	nwell_fed;

	num = philos->args->ph_num;
	while (1)
	{
		i = 0;
		nwell_fed = 0;
		while (i < num)
		{
			nwell_fed += philos[i].nmeals >= philos[i].args->must_eat_n;
			if (nwell_fed == num || check_philo_state(philos + i))
			{
				set_philos_states_as_over(philos);
				return (0);
			}
			i++;
		}
		usleep(5);
	}
	return (1);
}
