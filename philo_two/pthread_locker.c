#include "philosophers.h"

t_locker	*pthread_locker_init(const char *name, size_t value)
{
	t_locker	*sem;

	sem = sem_open(name, O_CREAT | O_EXCL, 0744, value);
	if (sem == SEM_FAILED)
	{
		if (errno == EEXIST)
		{
			sem_unlink(name);
			sem = sem_open(name, O_CREAT, 0744, value);
			if (sem == SEM_FAILED)
				return (NULL);
		}
		else
			return (NULL);
	}
	return (sem);
}

int	pthread_locker_destroy(t_locker *locker, const char *name)
{
	int	err;

	err = 0;
	if (locker != NULL)
		err = sem_close(locker);
	err |= sem_unlink(name);
	return (err);
}

int	pthread_lock(t_locker *locker)
{
	return (sem_wait(locker));
}

int	pthread_unlock(t_locker *locker)
{
	return (sem_post(locker));
}
