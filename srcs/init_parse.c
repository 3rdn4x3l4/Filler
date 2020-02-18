/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 13:57:58 by alagache          #+#    #+#             */
/*   Updated: 2020/02/18 14:16:12 by alagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include "ft_printf.h"

int		read_to_str(t_filler *info)
{
	char	*str;
	char	buff[BUFF_SIZE + 1];
	int		ret;
	size_t	len;

	len = 0;
	str = ft_strnew(0);
	if (str == NULL)
		return (STR_ERROR);
	while ((ret = read(0, buff, BUFF_SIZE)) > 0 && (len += ret) <= MAX_LEN)
	{
		buff[ret] = '\0';
		str = ft_strjoinfree(str, buff, 1);
	}
	if (len > MAX_LEN || ret == -1)
	{
		if (str != NULL)
			free(str);
		return (READ_ERROR);
	}
	info->stock = str;
	return(0);
}

int		str_to_arr(t_filler *info)
{
	info->arr = ft_strsplit(info->stock, '\n');
	if (info->arr == NULL)
		return (ARR_MALLOC);
	free(info->stock);
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

void	init_arrs(t_filler *info)
{
	int	i;

	i = 0;
	while (info->arr[i] != NULL && ft_strncmp(info->arr[i], "Plateau ", 8) != 0)
		i++;
	info->board = &(info->arr[i]);
	while (info->arr[i] != NULL && ft_strncmp(info->arr[i], "Piece ", 6) != 0)
		i++;
	info->piece = &(info->arr[i]);
}

int		get_arrs(t_filler *info, int turn)
{
	int		ret;

	ret = read_to_str(info);
	if (ret == STR_ERROR || ret == READ_ERROR)
		return (ERROR);
	ret = str_to_arr(info);
	if (ret == ARR_ERROR)
		return (ERROR);
	if (turn == 0)
		get_player_id(info);
	init_arrs(info);
	return (0);
}
