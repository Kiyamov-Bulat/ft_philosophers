#include "utils.h"

static size_t	atou_safe(const char *str, int *error)
{
	return (str_to_msec(str, error));
}

static int	parse_timeto_args(char *argv[], t_args *pa)
{
	int			i;
	int			err;
	t_msec		**fields;
	const char	*fields_str[] = {"[time_to_die]", \
		"[time_to_eat]", "[time_to_sleep]"};

	i = 0;
	fields = (t_msec *[]){&pa->die_time, &pa->eat_time, &pa->sleep_time, NULL};
	while (fields[i])
	{
		*fields[i] = str_to_msec(argv[i], &err);
		if (err)
			return (error(fields_str[i]) && error(" is not a valid!\n"));
		++i;
	}
	return (0);
}

int	parse_args(int argc, char *argv[], t_args *pa)
{
	int				err;

	if (argc < NUM_OF_ARGS)
		return (error("Wrong number of arguments!\n"));
	pa->ph_num = atou_safe(*(argv + 1), &err);
	if (err || pa->ph_num < 2)
		return (error("[number_of_philosophers] is not valid!\n"));
	if (parse_timeto_args(argv + 2, pa))
		return (1);
	if (argc == NUM_OF_ARGS + 1)
	{
		pa->must_eat_n = atou_safe(argv[NUM_OF_ARGS], &err);
		if (err)
			return (error("[number_of_times_each_philosopher_must_eat] \
				is not a valid!\n"));
	}
	else
		pa->must_eat_n = -1;
	return (0);
}
