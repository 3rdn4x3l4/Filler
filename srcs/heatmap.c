/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <alagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 15:55:49 by alagache          #+#    #+#             */
/*   Updated: 2020/04/13 15:55:51 by alagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"

static	int		has_zero(t_filler *info)
{
	int lne;
	int col;
	int	lne_max;
	int	col_max;

	lne_max = info->b_line;
	col_max = info->b_column;
	lne = 0;
	while (lne < lne_max)
	{
		col = 0;
		while (col < col_max)
		{
			if (info->map[lne][col] == 0)
				return (TRUE);
			col++;
		}
		lne++;
	}
	return (FALSE);
}

/*
** take short in an arr and test it's neighbours
*/

static	void	fill_around(const short new_value, t_filler *info,
							const int lne, const int col)
{
	short	**arr;

	arr = info->map;
	if (lne - 1 >= 0 && arr[lne - 1][col] == 0)
		arr[lne - 1][col] = new_value;
	if (col + 1 < info->b_column && arr[lne][col + 1] == 0)
		arr[lne][col + 1] = new_value;
	if (lne + 1 < info->b_line && arr[lne + 1][col] == 0)
		arr[lne + 1][col] = new_value;
	if (col - 1 >= 0 && arr[lne][col - 1] == 0)
		arr[lne][col - 1] = new_value;
}

/*
** it take as input a short** and assumes it is populated by 0/-1/-2
** finds any to_find value next to a 0 (N_E_S_W)
** and assign to this 0 the new value
** to_find is at first OP_VALUE and then is the new_value from previous call
** new_value is 1 at first (> 0 obviously) then is new_value + 1;
*/

static	void	one_pass_arr(t_filler *info, const short to_find,
							const short new_value)
{
	int lne;
	int col;
	int	lne_max;
	int	col_max;

	lne_max = info->b_line;
	col_max = info->b_column;
	lne = 0;
	while (lne < lne_max)
	{
		col = 0;
		while (col < col_max)
		{
			if (info->map[lne][col] == to_find)
				fill_around(new_value, info, lne, col);
			col++;
		}
		lne++;
	}
}

static	void	fill_zeros(t_filler *info, int value)
{
	int	l;
	int	c;

	l = 0;
	c = 0;
	while (l < info->b_line)
	{
		while (c < info->b_column)
		{
			if (info->map[l][c] == 0)
				info->map[l][c] = value;
			c++;
		}
		l++;
	}
}

void			fill_heatmap(t_filler *info)
{
	short	new_value;
	short	to_find;

	new_value = 1;
	to_find = OP_VALUE;
	while (has_zero(info) == TRUE && to_find * to_find
			<= info->b_line * info->b_line + info->b_column * info->b_column)
	{
		one_pass_arr(info, to_find, new_value);
		to_find = new_value;
		new_value++;
	}
	if (has_zero(info) == TRUE)
		fill_zeros(info, (to_find + 1) * (to_find + 1));
	get_piece_offset(info);
}
