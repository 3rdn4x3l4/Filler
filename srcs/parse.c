/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 14:04:07 by alagache          #+#    #+#             */
/*   Updated: 2020/02/18 18:04:20 by alagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include "ft_printf.h"

void	get_sizes(t_filler *info)
{
	char	*board;
	char	*piece;

	board = *(info->board);
	piece = *(info->piece);

	info->b_line = ft_atoi(ft_strchr(board, ' '));
	info->b_column = ft_atoi(ft_strrchr(board, ' '));
	info->p_line = ft_atoi(ft_strchr(piece, ' '));
	info->p_column = ft_atoi(ft_strrchr(piece, ' '));
}

void	init_ptrs(t_filler *info)
{
	int	i;

	i = 0;
	while (info->arr[i] != NULL && ft_strncmp(info->arr[i], "000 ", 4) != 0)
		i++;
	info->board = &(info->arr[i]);
	while (info->arr[i] != NULL && ft_strncmp(info->arr[i], "Piece ", 6) != 0)
		i++;
	info->piece = &(info->arr[i + 1]);
}

int		create_arrs(t_filler *info)
{
	size_t	map_size;
	size_t	shape_size;

	map_size = sizeof(short*) * (info->b_line + 1);
	shape_size = sizeof(short*) * (info->p_line + 1);
	info->map = (short**)malloc(map_size);
	if (info->map == NULL)
		return (ERR_MAP);
	info->shape = (short**)malloc(shape_size);
	if (info->shape == NULL)
	{
		free(info->map);
		return (ERR_SHAPE);
	}
	ft_memset(info->map, '\0', map_size);
	ft_memset(info->shape, '\0', shape_size);
	return (SUCCESS);
}

void	print_map(t_filler *info)
{
	int	i;
	int	j;

	i = 0;
	while (i < info->b_line)
	{
		j = 0;
		while (j < info->b_column)
		{
			dprintf(info->fd, "%6hi", info->map[i][j]);
			j++;
		}
		dprintf(info->fd, "\n");
		dprintf(info->fd, "\n");
		i++;
	}
}

void	fill_map_line(char *str, short *line, const int size, t_filler *info)
{
	int	i;
	char	*op;

	op = info->id_op;
	i = 0;
	while (i < size)
	{
		if (ft_strchr(info->id_op, str[i]) != NULL)
			line[i] = OP_VALUE;
		else if (ft_strchr(info->id, str[i]) != NULL)
			line[i] = MY_VALUE;
		i++;
	}
}

int		fill_map_arr(t_filler *info)
{
	int		i;
	int		size;

	i = 0;
	size = sizeof(short) * info->b_column;
	while (i < info->b_line)
	{
		info->map[i] = (short*)malloc(size);
		if (info->map[i] == NULL)
			return (ERROR);
		ft_memset(info->map[i], '\0', size);
		fill_map_line(info->board[i] + 4, info->map[i], info->b_column, info);
		i++;
	}
	return (SUCCESS);
}

void	print_shape(t_filler *info)
{
	int	i;
	int	j;

	i = 0;
	while (i < info->p_line)
	{
		j = 0;
		while (j < info->p_column)
		{
			dprintf(info->fd, "%6hi", info->shape[i][j]);
			j++;
		}
		dprintf(info->fd, "\n");
		i++;
	}
}

void	fill_shape_line(char *str, short *line, const int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (str[i] == '*')
			line[i] = PIECE_VALUE;
		i++;
	}
}

int		fill_shape_arr(t_filler *info)
{
	int		i;
	int		size;
		
	i = 0;
	size = sizeof(short) * info->p_column;
	while (i < info->p_line)
	{
		info->shape[i] = (short*)malloc(size);
		if (info->shape[i] == NULL)
			return (ERROR);
		ft_memset(info->shape[i], '\0', size);
		fill_shape_line(info->piece[i], info->shape[i], info->p_column);
		i++;
	}
	print_shape(info);
	return (SUCCESS);
}

int		has_zero(t_filler *info)
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
void	fill_around(const short new_value, t_filler *info, const int lne,
					const int col)
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
void	one_pass_arr(t_filler *info, const short to_find, const short new_value)
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

void	fill_heatmap(t_filler *info)
{
	short	new_value;
	short	to_find;

	new_value = 1;
	to_find = OP_VALUE;
	while (has_zero(info) == TRUE)
	{
		one_pass_arr(info, to_find, new_value);
		to_find = new_value;
		new_value++;
	}
	print_map(info);
}

void	line_offset(t_filler *info)
{
	int	lne;
	int	col;

	lne = 0;
	info->lne_offset = -1;
	while (lne < info->p_line && info->lne_offset == -1)
	{
		col = 0;
		while(col < info->p_column && info->shape[lne][col] == 0)
			col++;
		if (col == info->p_column)
			lne++;
		else
			info->lne_offset = lne;
	}
}

void	column_offset(t_filler *info)
{
	int	lne;
	int	col;

	col = 0;
	info->col_offset = -1;
	while (col < info->p_column && info->col_offset == -1)
	{
		lne = 0;
		while(lne < info->p_line && info->shape[lne][col] == 0)
			lne++;
		if (lne == info->p_line)
			col++;
		else
			info->col_offset = col;
	}
}

/*
** takes a pointer to the main struct
** find the offset of the shape inside the array
*/
void	get_piece_offset(t_filler *info)
{
	line_offset(info);
	column_offset(info);
}

void	line_diff(t_filler *info)
{
	int	lne;
	int	col;
	int	diff;

	lne = info->p_line - 1;
	diff = -1;
	while (lne >= 0 && diff == -1)
	{
		col = info->p_column - 1;
		while(col >= 0 && info->shape[lne][col] == 0)
			col--;
		if (col == -1)
			lne--;
		else
			diff = lne;
	}
	info->p_line -= diff;
}

void	column_diff(t_filler *info)
{
	int	lne;
	int	col;
	int	diff;

	col = info->p_column - 1;
	diff = -1;
	while (col >= 0 && diff == -1)
	{
		lne = info->p_line - 1;
		while(lne >= 0 && info->shape[lne][col] == 0)
			lne--;
		if (lne == -1)
			col--;
		else
			diff = col;
	}
	info->p_column -= diff;
}

/*
** recalc the piece size to only test line and column that contains a piece part
*/
void	effective_piece_size(t_filler *info)
{
	line_diff(info);
	column_diff(info);
}

void	free_allocs(t_filler *info)
{
	free_arr((void**)info->map);
	free_arr((void**)info->shape);
	free_arr((void**)info->arr);
}

void	update_best_coord(t_filler *info, int lne, int col)
{
	info->best_lne = lne ;//+ info->lne_offset;
	info->best_col = col ;//+ info->col_offset;
}

/*
** init search at 0 offset
** get best heatscore and note the coord
** might take into account same heatscore and decide which pair of coord to keep
*/
void	get_best_move(t_filler *info)
{
	int	lne;
	int	col;
	int	ret;
	int	heatscore;

	heatscore = INT_MAX;
	lne = 0 - info->lne_offset;
	// lne/col + piece_size < map_size
	while (lne + info->p_line < info->b_line)
	{
		col = 0 - info->col_offset;
		while (col + info->p_column < info->b_column)
		{
			if (is_placable(info, lne, col) == TRUE)
			{
				ret = get_heat_score(info, lne, col);
				if (ret < heatscore)
				{
					update_best_coord(info, lne, col);
				}
			}
			col++;
		}
		lne++;
	}
}

void	play_best_move(t_filler *info)
{
	printf("%i %i\n", info->best_lne, info->best_col);
}

int		parse(t_filler *info, int turn)
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
