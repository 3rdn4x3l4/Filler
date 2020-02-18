#include "filler.h"
#include "libft.h"

int			main(void)
{
	int			ret;
	int			turn;
	t_filler	info;

	ft_bzero(&info, sizeof(info));
	turn = 0;
	while (1)
	{
		ret = parse(&info, turn);
		if (ret != 0)
			return (EXIT_FAILURE);
		turn++;
		while (1)
		{
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
