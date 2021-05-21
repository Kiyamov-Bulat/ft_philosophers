#include "utils.h"

t_msec	str_to_msec(const char *str, int *error)
{
	t_msec	res;

	res = 0;
	while (ft_isspace(*str))
		str++;
	str += *str == '+';
	if (*str == '\0')
	{
		*error = 1;
		return (0);
	}
	while (ft_isdigit(*str))
		res = res * 10 + *str++ - '0';
	if (*str != '\0')
		*error = 1;
	else
		*error = 0;
	return (res);
}
