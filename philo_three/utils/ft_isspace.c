#include "utils.h"

int	ft_isspace(int c)
{
	return (('\t' <= c && c <= '\r') || c == ' ');
}
