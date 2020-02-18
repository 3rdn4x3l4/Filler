/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 14:04:07 by alagache          #+#    #+#             */
/*   Updated: 2020/02/18 15:33:22 by alagache         ###   ########.fr       */
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
	//ft_printf("|init_ptrs|\n%s\n%s\n", *(info->board), *(info->piece));
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
	return (0);
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
			printf("%6hi", info->map[i][j]);
			j++;
		}
		printf("\n");
		printf("\n");
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
	size = sizeof(short) * (info->b_column + 1);
	while (i < info->b_line)
	{
		info->map[i] = (short*)malloc(size);
		if (info->map[i] == NULL)
			return (ERROR);
		ft_memset(info->map[i], '\0', size);
		fill_map_line(info->board[i] + 4, info->map[i], info->b_column, info);
		i++;
	}
	//print_map(info);
	return (0);
}

//shape
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
			printf("|%hi|", info->shape[i][j]);
			j++;
		}
		printf("\n");
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
	size = sizeof(short) * (info->p_column + 1);
	while (i < info->p_line)
	{
		info->shape[i] = (short*)malloc(size);
		if (info->shape[i] == NULL)
			return (ERROR);
		ft_memset(info->shape[i], '\0', size);
		fill_shape_line(info->piece[i], info->shape[i], info->p_column);
		i++;
	}
	//print_shape(info);
	return (0);
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
** to_find is at first OP_value and then is the new_value from previous call
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

void	free_allocs(t_filler *info)
{
	free_arr((void**)info->map);
	free_arr((void**)info->shape);
	free_arr((void**)info->arr);
}

int		parse(t_filler *info, int turn)
{
	int		ret;

	ret = get_arrs(info, turn);
	if (ret == ERROR)
		return (ERROR);
	get_sizes(info);
	init_ptrs(info);
	create_arrs(info);
	fill_map_arr(info);
	fill_shape_arr(info);
	fill_heatmap(info);
	get_piece_offset(info);
	//parsing done
	//get_best_pos();
	//print_best_pos();
	free_allocs(info);
	return (0);
}

/*
int		get_best_pos()
{
}

int		print_best_pos()
{
}
*/

