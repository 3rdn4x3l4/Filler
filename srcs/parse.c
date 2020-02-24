/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:00:24 by alagache          #+#    #+#             */
/*   Updated: 2020/02/24 16:56:17 by alagache         ###   ########.fr       */
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
	//piece placable in HEIGHT lne
	while (lne + info->p_line < info->b_line)
	{
		col = 0 - info->col_offset;
		//piece placable in width col
		while (col + info->p_column < info->b_column)
		{
			if (is_placable(info, lne, col) == TRUE)
			{
				ret = get_heat_score(info, lne, col);
				info->best_lne = (ret < heatscore ? lne : info->best_lne);
				info->best_col = (ret < heatscore ? col : info->best_col);
			}
			col++;
		}
		lne++;
	}
}

void			play_best_move(t_filler *info, int turn)
{
	ft_dprintf(info->fd, "PLAYED %i %i at turn %i\n", info->best_lne, info->best_col, turn);
	ft_printf("%i %i\n", info->best_lne, info->best_col);
}

void			free_allocs(t_filler *info)
{
	free_arr((void**)info->map);
	free_arr((void**)info->shape);
	free_arr((void**)info->arr);
}

void			clean_struct(t_filler *info)
{
	info->map = NULL;
	info->shape = NULL;
	info->board = NULL;
	info->piece = NULL;
	info->arr = NULL;
	info->stock = NULL;
	info->b_line = 0;
	info->b_column = 0;
	info->p_line = 0;
	info->p_column = 0;
	info->lne_offset = 0;
	info->col_offset = 0;
	info->heatscore = 0;
	info->best_lne = 0;
	info->best_col = 0;
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
	//print
	print_map(info);
	ft_dprintf(info->fd, "\n");
	print_shape(info);
	ft_dprintf(info->fd, "\n");
	//print
	get_piece_offset(info);
	effective_piece_size(info);
	get_best_move(info);
	print_info(info);
	free_allocs(info);
	play_best_move(info, turn);
	while (1)
	{
	}
	clean_struct(info);
	return (SUCCESS);
}
