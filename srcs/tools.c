/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:13:40 by alagache          #+#    #+#             */
/*   Updated: 2020/02/27 14:26:32 by alagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	l = info->lne_offset;
	self = 0;
	while (l < info->p_line)
	{
		c = info->col_offset;
		while (c < info->p_column)
		{
			if (info->shape[l][c] == PIECE_VALUE
				&& info->map[l + lne][c + col] == OP_VALUE)
				return (FALSE);
			if (info->shape[l][c] == PIECE_VALUE
				&& info->map[l + lne][c + col] == MY_VALUE)
				self += 1;
			c++;
		}
		l++;
	}
	if (self == 1)
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
			if (info->shape[l][c] == PIECE_VALUE
				&& info->map[l + lne][c + col] > 0)
				heatscore += info->map[l + lne][c + col];
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

void	clean_struct(t_filler *info)
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
	info->play = 0;
	info->best_lne = 0;
	info->best_col = 0;
}

void	free_allocs(t_filler *info)
{
	free_arr((void**)info->map);
	free_arr((void**)info->shape);
	free_arr((void**)info->arr);
}
