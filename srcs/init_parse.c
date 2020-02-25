/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:03:17 by alagache          #+#    #+#             */
/*   Updated: 2020/02/24 17:34:35 by alagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include "ft_printf.h"

int		end_of_read(char *str)
{
	int		i;
	int		nbr;
	char	*ptr;

	if ((ptr = ft_strstr(str, "Piece ")) == NULL)
		return (FAILURE);
	if (ft_strrchr(ptr, ':') == NULL)
		return (FAILURE);
	nbr = ft_atoi(ptr + 5);
	i = 0;
	while (ptr[i])
		nbr -= (ptr[i++] == '\n' ? 1 : 0);
	if (nbr != -1)
		return (FAILURE);
	return (SUCCESS);
}

int		read_to_str(t_filler *info)
{
	char	*str;
	char	buff[BUFF_SIZE + 1];
	int		ret;

	str = ft_strnew(0);
	if (str == NULL)
		return (STR_ERROR);
	while (end_of_read(str) == FAILURE)
	{
		ret = read(0, buff, BUFF_SIZE);
		buff[ret] = '\0';
		str = ft_strjoinfree(str, buff, 1);
	}
	info->stock = str;
	return (0);
}

void	get_player_id(t_filler *info)
{
	if (info->arr[0][10] == '1')
	{
		info->id[0] = 'O';
		info->id[1] = 'o';
		info->id_op[0] = 'X';
		info->id_op[1] = 'x';
	}
	else
	{
		info->id_op[0] = 'O';
		info->id_op[1] = 'o';
		info->id[0] = 'X';
		info->id[1] = 'x';
	}
}

int		init_arrs(t_filler *info, int turn)
{
	int	i;

	info->arr = ft_strsplit(info->stock, '\n');
	if (info->arr == NULL)
		return (ARR_MALLOC);
	free(info->stock);
	if (turn == 0)
		get_player_id(info);
	i = 0;
	while (info->arr[i] != NULL && ft_strncmp(info->arr[i], "Plateau ", 8) != 0)
		i++;
	info->board = &(info->arr[i]);
	while (info->arr[i] != NULL && ft_strncmp(info->arr[i], "Piece ", 6) != 0)
		i++;
	info->piece = &(info->arr[i]);
	return (0);
}

int		get_arrs(t_filler *info, int turn)
{
	int		ret;

	ret = read_to_str(info);
	if (ret == STR_ERROR || ret == READ_ERROR)
		return (ERROR);
	ret = init_arrs(info, turn);
	if (ret == ARR_ERROR)
		return (ERROR);
	return (0);
}
