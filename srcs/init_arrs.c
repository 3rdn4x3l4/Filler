/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arrs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:27:43 by alagache          #+#    #+#             */
/*   Updated: 2020/02/21 16:00:04 by alagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"

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
