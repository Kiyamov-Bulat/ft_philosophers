#include "philosophers.h"

int	start_act(t_philo *philo, const char *msg, t_msec dur)
{
	t_msec	end;
	t_msec	portion;

	if (philo->is_over)
		return (1);
	end = get_current_time_ms() + dur;
	portion = dur / PORTION_DEVIDER;
	if (print_philo_status(philo->id, msg) == -1)
		return (1);
	while (end > get_current_time_ms() && !philo->is_over)
	{
		if (usleep(portion))
			return (-1);
	}
	return (0);
}
