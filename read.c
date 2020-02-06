#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "filler.h"
#include "libft/includes/libft.h"
#include "libft/includes/ft_printf.h"

//int		player_info(t_filler *info, int turn)
//{
//	if (turn != 0)
//		return (PLAYER_OK);
//	if (ft_strnstr(info->stock, "$$$ exec p", 10) == NULL)
//		return (NO_PLAYER);
//	info->piece_id = (info->stock[10] == 1) ? "Oo" : "Xx";
//	info->piece_id_op = (ft_strcmp(info->piece_id, "Oo") == 0) ? "Xx" : "Oo";
//	return (PLAYER_OK);
//}

//int		board_info(t_filler *info)
//{
//	//int ret;
//
//	if (info->pos == NULL)
//		return (BOARD_ERROR);
//	if (can_fetch_nbr(info->pos) == FALSE)
//		return (BOARD_ERROR);
//	info->line_b = atoi(info->pos + 7);
//	info->column_b = atoi(ft_strchr(info->pos + 8, ' '));
//	//ret = board_content(info);
//	//if (ret == BOARD_ERROR)
//	//	return (BOARD_ERROR);
//	return (BOARD_OK);
//}

//int		piece_info(t_filler *info)
//{
//	if (info->pos == NULL)
//		return (PIECE_ERROR);
//	if (can_fetch_nbr(info->pos) == FALSE)
//		return (PIECE_ERROR);
//	info->line_p = atoi(info->pos + 6);
//	info->column_p = atoi(ft_strchr(info->pos + 7, ' '));
//	//if (piece_content(info) == PIECE_ERROR)
//	//	return (PIECE_ERROR);
//	return (PIECE_OK);
//}

//void	print_alloc(t_filler *info)
//{
//	int	i;
//
//	i = 0;
//	while (info->arr_stock[i] != NULL)
//	{
//		ft_dprintf(info->fd_debug, "%s\n", info->arr_stock[i]);
//		i++;
//	}
//	i = 0;
//	ft_dprintf(info->fd_debug, "|||||||||\n");
//	while (i < info->line_b)
//	{
//		ft_dprintf(info->fd_debug, "%s\n", info->arr_b[i]);
//		i++;
//	}
//	i = 0;
//	ft_dprintf(info->fd_debug, "|||||||||\n");
//	while (i < info->line_p)
//	{
//		ft_dprintf(info->fd_debug, "%s\n", info->arr_p[i]);
//		i++;
//	}
//	ft_dprintf(info->fd_debug, "%sI am %s\nOp is %s\n",info->stock,  info->piece_id, info->piece_id_op);
//	ft_dprintf(info->fd_debug, "lne_b = %i\ncol_b = %i\n", info->line_b, info->column_b);
//	ft_dprintf(info->fd_debug, "line_p = %i\ncolumn_p = %i\n", info->line_p, info->column_p);
//}

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
	info->arr_stock = ft_strsplit(info->stock, '\n');
	if (info->arr_stock == NULL)
		return (ARR_MALLOC);
	return (0);
}

void		reallign_board(t_filler *info)
{
	char	**str_add;
	int		len;

	str_add = info->arr_stock;
	while (*str_add != NULL && ft_strcmp(*str_add, "000 ") != 0)
		str_add++;
	len = ft_strlen(*str_add);
	while (ft_strcmp(*str_add, "Piece ") != 0)
	{
		ft_memmove(*str_add, (*str_add) + 4, len - 4);
		str_add++;
	}
}

void	init_ptrs(t_filler *info)
{
	char	**arr;

	arr = info->arr_stock;
	while (*str_add != NULL && ft_strcmp(*str_add, "000 ") != 0)
		str_add++;
	info->board = str_add;
	while (*str_add != NULL && ft_strcmp(*str_add, "Piece ") != 0)
		str_add++;
	info->piece = str_add + 1;
}

int		get_board_size()
{
}

int		get_piece_rsize()
{
}

int		get_piece_offset()
{
}

void	fill_heatmap()
{
}

int		get_best_pos()
{
}

int		print_best_pos()
{
}

int		parse(t_filler *info, int turn)
{
	int		ret;

	ret = read_to_str(info);
	if (ret == STR_ERROR || ret == READ_ERROR)
		return (ERROR);
	ret = str_to_arr(info);
	if (ret == ARR_ERROR)
		return (ERROR);
	print_alloc(info);
	return (0);
}
