/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arrs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <alagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 15:55:56 by alagache          #+#    #+#             */
/*   Updated: 2020/04/16 15:25:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdlib.h>

int		check_piece_size(t_filler *info)
{
	int	i;
	int	c;

	i = 0;
	while (info->piece[i])
	{
		c = 0;
		while (info->piece[i][c] && c < info->p_column + 1)
			c++;
		if (c != info->p_column)
		{
			free_arr((void**)info->arr);
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int		check_sizes(t_filler *info)
{
	int	i;
	int	c;

	i = 0;
	while (info->board[i] && i < info->b_line + 1
			&& info->board + i != info->piece - 1)
	{
		c = 0;
		while (info->board[i][c] && c < info->b_column + 5)
			c++;
		if (c != info->b_column + 4)
		{
			free_arr((void**)info->arr);
			return (ERROR);
		}
		i++;
	}
	if (i != info->b_line)
	{
		free_arr((void**)info->arr);
		return (ERROR);
	}
	if (check_piece_size(info) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

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
