#include "philosophers.h"

int	pthread_lock(t_locker *locker)
{
	return (pthread_mutex_lock(locker));
}

int	pthread_unlock(t_locker *locker)
{
	return (pthread_mutex_unlock(locker));
}
