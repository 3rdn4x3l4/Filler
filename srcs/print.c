/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:09:01 by alagache          #+#    #+#             */
/*   Updated: 2020/02/21 17:20:39 by alagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "ft_printf.h"

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
			ft_dprintf(info->fd, "%6hi", info->map[i][j]);
			j++;
		}
		ft_dprintf(info->fd, "\n");
		ft_dprintf(info->fd, "\n");
		i++;
	}
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
			ft_dprintf(info->fd, "%6hi", info->shape[i][j]);
			j++;
		}
		ft_dprintf(info->fd, "\n");
		i++;
	}
}

void	print_info(t_filler *info)
{
	ft_dprintf(info->fd, "lne_off = %i||col_off = %i\n", info->lne_offset, info->col_offset);
	ft_dprintf(info->fd, "lne_sze = %i||col_sze = %i\n", info->p_line, info->p_column);
	ft_dprintf(info->fd, "lne_bst = %i||col_bst = %i\n", info->best_lne, info->best_col);
}
