#include "utils.h"

static t_msec	g_start_of_simulation;

static t_msec	get_time_ms(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == -1)
		return (0);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

int	init_start_of_simulation(void)
{
	g_start_of_simulation = get_time_ms();
	return (!g_start_of_simulation);
}

t_msec	get_current_time_ms(void)
{
	t_msec	ctime;

	ctime = get_time_ms();
	if (ctime)
		return (ctime - g_start_of_simulation);
	return (0);
}
