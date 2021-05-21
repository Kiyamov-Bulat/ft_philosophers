#include "philosophers.h"

int	print_philo_status(size_t ph_num, const char *status)
{
	int				n;
	static t_locker	locker = PTHREAD_MUTEX_INITIALIZER;

	if (!*status)
		return (0);
	pthread_lock(&locker);
	n = printf("%llu %lu %s\n", get_current_time_ms(), ph_num, status);
	pthread_unlock(&locker);
	return (n);
}
