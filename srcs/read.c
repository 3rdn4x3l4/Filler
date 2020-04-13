#include "filler.h"

int	check_read(char *str, int len)
{
	int	i;

	i = -1;
	str[len] = '\0';
	while (++i < len)
	{
		if (str[i] <= 0)
			return (FAILURE);
	}
	return (SUCCESS);
}
