#include "utils.h"

int	error(const char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (1);
}
