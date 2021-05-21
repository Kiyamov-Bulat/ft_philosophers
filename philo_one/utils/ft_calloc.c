#include "utils.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	char	*cp;
	void	*mem;

	i = 0;
	mem = malloc(nmemb * size);
	if (mem == NULL)
		return (NULL);
	cp = (char *)mem;
	while (i < nmemb)
	{
		ft_bzero(cp, size);
		i++;
		cp += size;
	}
	return (mem);
}
