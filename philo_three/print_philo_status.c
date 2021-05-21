#include "philosophers.h"

static t_locker	*g_print_locker;

int	init_print_locker(void)
{
	g_print_locker = pthread_locker_init(PRINT_SEM_NAME, 1);
	return (g_print_locker == NULL);
}

int	destroy_print_locker(void)
{
	return (pthread_locker_destroy(g_print_locker, PRINT_SEM_NAME));
}

int	print_philo_status(size_t ph_num, const char *status)
{
	int	n;

	if (!*status)
		return (0);
	pthread_lock(g_print_locker);
	n = printf("%llu %lu %s\n", get_current_time_ms(), ph_num, status);
	pthread_unlock(g_print_locker);
	return (n);
}
