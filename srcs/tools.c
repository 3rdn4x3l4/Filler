#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "filler.h"
#include "libft.h"
#include "ft_printf.h"

/*
** take a pointer to the main struct and a pair of coord
** assumes the pair of coord is OK
** return TRUE if shape is placable at this coord
** placable means:
** 1 colision with self
** 0 colision with opponent
*/
int		is_placable(t_filler *info, int lne, int col)
{
	int	l;
	int	c;

	l = 0;
	info->self = 0;
	info->oppo = 0;
	while (l < info->p_line && info->self <= 1 && info->oppo == 0)
	{
		c = 0;
		while (c < info->p_column && info->self <= 1 && info->oppo == 0)
		{
			if (info->shape[l + info->lne_offset][c + info->col_offset]
				== PIECE_VALUE)
			{
				info->self += (info->map[l + lne][c + col] == MY_VALUE ? 1 : 0);
				info->oppo += (info->map[l + lne][c + col] == OP_VALUE ? 1 : 0);
			}
			c++;
		}
		l++;
	}
	if (info->self == 1 && info->oppo == 0)
		return (TRUE);
	return (FALSE);
}

/*
** take a pointer to the main struct and a pair of coord
** calculate the heatscore for the given set of coord
*/
int		get_heat_score(t_filler *info, int lne, int col)
{
	int	l;
	int	c;
	int	heatscore;

	heatscore = 0;
	l = 0;
	while (l < info->p_line)
	{
		c = 0;
		while (c < info->p_column)
		{
			if (info->shape[l + info->lne_offset][c + info->col_offset]
				== PIECE_VALUE)
				heatscore += (info->map[l + lne][c + col] > 0 ?
								info->map[l + lne][c + col] : 0);
			c++;
		}
		l++;
	}
	return (heatscore);
}

void	free_arr(void **arr)
{
	int		i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
