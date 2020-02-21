/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:00:24 by alagache          #+#    #+#             */
/*   Updated: 2020/02/21 16:04:51 by alagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include "ft_printf.h"

static	void	update_best_coord(t_filler *info, int lne, int col)
{
	info->best_lne = lne;
	info->best_col = col;
}

/*
** init search at 0 offset
** get best heatscore and note the coord
** might take into account same heatscore and decide which pair of coord to keep
*/

void			get_best_move(t_filler *info)
{
	int	lne;
	int	col;
	int	ret;
	int	heatscore;

	heatscore = INT_MAX;
	lne = 0 - info->lne_offset;
	while (lne + info->p_line < info->b_line)
	{
		col = 0 - info->col_offset;
		while (col + info->p_column < info->b_column)
		{
			if (is_placable(info, lne, col) == TRUE)
			{
				ret = get_heat_score(info, lne, col);
				if (ret < heatscore)
					update_best_coord(info, lne, col);
			}
			col++;
		}
		lne++;
	}
}

void			play_best_move(t_filler *info)
{
	ft_printf("%i %i\n", info->best_lne, info->best_col);
}

void			free_allocs(t_filler *info)
{
	free_arr((void**)info->map);
	free_arr((void**)info->shape);
	free_arr((void**)info->arr);
}

int				parse(t_filler *info, int turn)
{
	int		ret;

	ret = get_arrs(info, turn);
	if (ret == ERROR)
		return (ERROR);
	get_sizes(info);
	init_ptrs(info);
	ret = create_arrs(info);
	if (ret == ERR_MAP || ret == ERR_SHAPE)
		return (ERROR);
	ret = fill_map_arr(info);
	if (ret == ERROR)
		return (ERROR);
	ret = fill_shape_arr(info);
	if (ret == ERROR)
		return (ERROR);
	fill_heatmap(info);
	get_piece_offset(info);
	effective_piece_size(info);
	get_best_move(info);
	play_best_move(info);
	free_allocs(info);
	return (0);
}
