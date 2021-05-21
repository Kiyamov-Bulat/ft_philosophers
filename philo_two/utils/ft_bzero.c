#include "utils.h"

void	ft_bzero(void *s, size_t n)
{
	char	*ps;

	ps = (char *)s;
	while (n-- > 0)
		*ps++ = '\0';
}
