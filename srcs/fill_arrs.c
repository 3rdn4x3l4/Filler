/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_arrs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <alagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 15:55:44 by alagache          #+#    #+#             */
/*   Updated: 2020/04/14 13:37:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdlib.h>

static	void	fill_map_line(char *str, short *line, const int size,
								t_filler *info)
{
	int		i;

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

int				fill_map_arr(t_filler *info)
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

static	void	fill_shape_line(char *str, short *line, const int size)
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

int				fill_shape_arr(t_filler *info)
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
	return (SUCCESS);
}
