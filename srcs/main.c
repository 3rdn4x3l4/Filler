#include "filler.h"
#include "libft.h"
#include <fcntl.h>

int			main(void)
{
	int			ret;
	int			turn;
	t_filler	info;

	ft_bzero(&info, sizeof(info));
	turn = 0;
	info.fd = open("output.txt", O_CREAT|O_RDWR|O_APPEND);
	while (1)
	{
		ret = parse(&info, turn);
		if (ret != 0)
			return (EXIT_FAILURE);
		turn++;
	}
	return (EXIT_SUCCESS);
}
