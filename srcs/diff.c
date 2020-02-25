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
	i = max - 1;
	nb = 0;
	while (i >= 0)
	{
		nb += (mode == 0 && arr[l][c + i] == PIECE_VALUE ? 1 : 0);
		nb += (mode == 1 && arr[l + i][c] == PIECE_VALUE ? 1 : 0);
		if (nb != 0)
			return (FAILURE);
		i--;
	}
	return (SUCCESS);
}

/*
** recalc the piece size to only test line and column that contains a piece part
*/

void			effective_piece_size(t_filler *info)
{
	int	l;
	int	c;
	int	c_diff;
	int	l_diff;

	l = info->p_line - 1;
	c = info->p_column - 1;
	l_diff = -1;
	while (l >= 0 && l_diff == -1)
	{
		if (is_empty(l, info->p_column, 0, info->shape) == FAILURE)
			l_diff = l;
		l--;
	}
	c_diff = -1;
	while (c >= 0 && c_diff == -1)
	{
		if (is_empty(c, info->p_line, 1, info->shape) == FAILURE)
			c_diff = c;
		c--;
	}
	info->p_line = l_diff + 1;
	info->p_column = c_diff + 1;
	//ft_dprintf(info->fd, "diffL= %i || diffC = %i\n", l_diff, c_diff);
}
