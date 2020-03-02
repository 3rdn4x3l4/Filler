/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:00:24 by alagache          #+#    #+#             */
/*   Updated: 2020/02/27 14:28:54 by alagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include "ft_printf.h"

void			get_best_move(t_filler *info)
{
	int	lne;
	int	col;
	int	ret;
	int	heatscore;

	heatscore = INT_MAX;
	lne = 0 - info->lne_offset;
	while (lne + info->p_line <= info->b_line)
	{
		col = 0 - info->col_offset;
		while (col + info->p_column <= info->b_column)
		{
			if (is_placable(info, lne, col) == TRUE)
			{
				ret = get_heat_score(info, lne, col);
				info->best_lne = (ret < heatscore ? lne : info->best_lne);
				info->best_col = (ret < heatscore ? col : info->best_col);
				heatscore = (ret < heatscore ? ret : heatscore);
			}
			col++;
		}
		lne++;
	}
	if (heatscore == INT_MAX)
		info->play = -1;
}

int				parse(t_filler *info, int turn)
{
	int		ret;

	ret = get_arrs(info, turn);
	if (ret == ERROR)
		return (ERROR);
	get_sizes(info);
	init_ptrs(info);
	ret = check_sizes(info);
	if (ret == ERROR)
		return (ERROR);
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
	get_best_move(info);
	free_allocs(info);
	ft_printf("%i %i\n", info->best_lne, info->best_col);
	return (SUCCESS);
}
