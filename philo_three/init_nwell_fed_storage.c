#include "philosophers.h"

static t_locker	*g_nwell_fed;

int	init_nwell_fed_storage(void)
{
	g_nwell_fed = pthread_locker_init(PHILOS_NWELL_FED_SEM_NAME, 0);
	return (g_nwell_fed == NULL);
}

t_locker	*get_philos_nwell_fed(void)
{
	return (g_nwell_fed);
}

int	destroy_nwell_fed_storage(void)
{
	return (pthread_locker_destroy(g_nwell_fed, PHILOS_NWELL_FED_SEM_NAME));
}
