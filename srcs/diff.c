/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diff.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:45:44 by alagache          #+#    #+#             */
/*   Updated: 2020/02/21 17:14:11 by alagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include "ft_printf.h"

static	void	line_diff(t_filler *info)
{
	int	lne;
	int	col;
	int	diff;

	lne = info->p_line - 1;
	diff = -1;
	while (lne >= 0 && diff == -1)
	{
		col = info->p_column - 1;
		while (col >= 0 && info->shape[lne][col] == 0)
			col--;
		if (col == -1)
			lne--;
		else
			diff = lne;
	}
	info->p_line -= diff - 1;
}

static	void	column_diff(t_filler *info)
{
	int	lne;
	int	col;
	int	diff;

	col = info->p_column - 1;
	diff = -1;
	while (col >= 0 && diff == -1)
	{
		lne = info->p_line - 1;
		while (lne >= 0 && info->shape[lne][col] == 0)
			lne--;
		if (lne == -1)
			col--;
		else
			diff = col;
	}
	info->p_column -= diff -  1;
}

/*
** recalc the piece size to only test line and column that contains a piece part
*/

void			effective_piece_size(t_filler *info)
{
	line_diff(info);
	column_diff(info);
}
