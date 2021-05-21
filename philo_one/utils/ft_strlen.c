#include "utils.h"

size_t	ft_strlen(const char *s)
{
	const char	*ps;

	ps = s;
	while (*s)
		s++;
	return (s - ps);
}
