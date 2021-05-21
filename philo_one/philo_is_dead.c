#include "philosophers.h"

int	philo_is_dead(t_philo *philo)
{
	return (philo->last_meal + philo->args->die_time < get_current_time_ms());
}
