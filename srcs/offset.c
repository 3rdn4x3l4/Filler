/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <alagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 15:56:26 by alagache          #+#    #+#             */
/*   Updated: 2020/04/13 15:56:27 by alagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include "ft_printf.h"

/*
** given 3 int and a pointer to an array of short
** check if the line or column is empty of any shape
** mode 0 checks for a whole column
** mode 1 checks for a whole line
*/

static	int		is_empty(int fixed, int max, int mode, short **arr)
{
	int	c;
	int	l;
	int	i;
	int	nb;

	l = (mode == 0 ? fixed : 0);
	c = (mode == 0 ? 0 : fixed);
	i = 0;
	nb = 0;
	while (i < max)
	{
		nb += (mode == 0 && arr[l][c + i] == PIECE_VALUE ? 1 : 0);
		nb += (mode == 1 && arr[l + i][c] == PIECE_VALUE ? 1 : 0);
		if (nb != 0)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

/*
** takes a pointer to the main struct
** find the offset of the shape inside the array
*/

void			get_piece_offset(t_filler *info)
{
	int	l;
	int	c;

	l = 0;
	c = 0;
	info->lne_offset = -1;
	while (l < info->p_line && info->lne_offset == -1)
	{
		if (is_empty(l, info->p_column, 0, info->shape) == FAILURE)
			info->lne_offset = l;
		l++;
	}
	info->col_offset = -1;
	while (c < info->p_column && info->col_offset == -1)
	{
		if (is_empty(c, info->p_line, 1, info->shape) == FAILURE)
			info->col_offset = c;
		c++;
	}
	effective_piece_size(info);
}
