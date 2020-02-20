#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "filler.h"
#include "libft.h"
#include "ft_printf.h"

/*
** take a pointer to the main struct and a pair of coord
** assumes the pair of coord is normalized with piece offset
** and shape size is not too big to fit inside map
** this permit fallback onto map and check only the effective part of the shape
** return TRUE if shape is placable at this coord
** placable means:
** 1 colision with self
** 0 colision with opponent
*/
int		is_placable(t_filler *info, int lne, int col)
{
	int	l;
	int	c;
	int	self;
	int	oppo;

	l = info->lne_offset;
	self = 0;
	oppo = 0;
	while (l < info->p_line)
	{
		c = info->col_offset;
		while (c < info->p_column)
		{
			if (info->shape[l][c] == PIECE_VALUE)
			{
				self += (info->map[l + lne][c + col] == MY_VALUE ? 1 : 0);
				oppo += (info->map[l + lne][c + col] == OP_VALUE ? 1 : 0);
			}
			c++;
		}
		l++;
	}
	if (self == 1 && oppo == 0)
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
	l = info->lne_offset;
	while (l < info->p_line)
	{
		c = info->col_offset;
		while (c < info->p_column)
		{
			if (info->shape[l][c] == PIECE_VALUE)
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
