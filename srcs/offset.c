/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:45:27 by alagache          #+#    #+#             */
/*   Updated: 2020/02/21 15:47:30 by alagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"

static	void	line_offset(t_filler *info)
{
	int	lne;
	int	col;

	lne = 0;
	info->lne_offset = -1;
	while (lne < info->p_line && info->lne_offset == -1)
	{
		col = 0;
		while (col < info->p_column && info->shape[lne][col] == 0)
			col++;
		if (col == info->p_column)
			lne++;
		else
			info->lne_offset = lne;
	}
}

static	void	column_offset(t_filler *info)
{
	int	lne;
	int	col;

	col = 0;
	info->col_offset = -1;
	while (col < info->p_column && info->col_offset == -1)
	{
		lne = 0;
		while (lne < info->p_line && info->shape[lne][col] == 0)
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

void			get_piece_offset(t_filler *info)
{
	line_offset(info);
	column_offset(info);
}
