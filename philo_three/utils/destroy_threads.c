#include "utils.h"

int	destroy_threads(pthread_t *threads, size_t thread_num)
{
	size_t	i;
	int		err;

	i = 0;
	err = 0;
	while (i < thread_num)
		err |= pthread_join(threads[i++], NULL);
	free(threads);
	if (err)
		error("pthread_detach error!\n");
	return (err);
}
