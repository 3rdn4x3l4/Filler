/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <alagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 15:56:37 by alagache          #+#    #+#             */
/*   Updated: 2020/04/13 15:56:39 by alagache         ###   ########.fr       */
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
