#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "filler.h"
#include "libft/includes/libft.h"
#include "libft/includes/ft_printf.h"

/*
 * if first turn and has player info
 * init piece_id with the player charset
 * else do nothing
*/
int		player_info(t_filler *info, int turn)
{
	if (turn != 0)
		return (PLAYER_OK);
	if (ft_strnstr(info->stock, "$$$ exec p", 10) == NULL)
		return (NO_PLAYER);
	info->piece_id = (info->stock[10] == 1) ? "Oo" : "Xx";
	info->piece_id_op = (ft_strcmp(info->piece_id, "Oo") == 0) ? "Xx" : "Oo";
	return (PLAYER_OK);
}

int		board_info(t_filler *info)
{
	//int ret;

	if (info->pos == NULL)
		return (BOARD_ERROR);
	if (can_fetch_nbr(info->pos) == FALSE)
		return (BOARD_ERROR);
	info->line_b = atoi(info->pos + 7);
	info->column_b = atoi(ft_strchr(info->pos + 8, ' '));
	//ret = board_content(info);
	//if (ret == BOARD_ERROR)
	//	return (BOARD_ERROR);
	return (BOARD_OK);
}

int		piece_info(t_filler *info)
{
	if (info->pos == NULL)
		return (PIECE_ERROR);
	if (can_fetch_nbr(info->pos) == FALSE)
		return (PIECE_ERROR);
	info->line_p = atoi(info->pos + 6);
	info->column_p = atoi(ft_strchr(info->pos + 7, ' '));
	//if (piece_content(info) == PIECE_ERROR)
	//	return (PIECE_ERROR);
	return (PIECE_OK);
}

int		check_arr(t_filler *info, int turn)
{
	int ret;

	ret = player_info(info, turn);
	if (ret == NO_PLAYER)
		return (ret);
	info->pos = ft_strstr(info->stock, "Piece ");
	ret = piece_info(info);
	if (ret == PIECE_ERROR)
		return (ret);
	info->pos = ft_strstr(info->stock, "Plateau ");
	ret = board_info(info);
	if (ret == BOARD_ERROR)
		return (ret);
	return (STR_OK);
}

int		read_to_str(t_filler *info)
{
	char	buff[BUFF_SIZE + 1];
	int		ret;
	size_t	len;

	len = 0;
	while ((ret = read(0, buff, BUFF_SIZE)) > 0 && (len += ret) <= MAX_LEN)
	{
		buff[ret] = '\0';
		if (info->stock == NULL)
			info->stock = ft_strdup(buff);
		else
			info->stock = ft_strjoinfree(info->stock, buff, 1);
	}
	if (len > MAX_LEN)
	{
		free(info->stock);
		return (READ_ERROR);
	}
	if (ret == -1)
		return (READ_ERROR);
	return(0);
}

void		reallign_board(t_filler *info)
{
	char	**str_add;

	str_add = info->arr_stock;
	while (*str_add != NULL && ft_strstr(*str_add, "000 ") == NULL)
		str_add++;
	while ((*str_add)[3] == ' ')
	{
		ft_memmove(*str_add, (*str_add) + 4, ft_strlen(*str_add) - 4);
		str_add++;
	}
}

int		str_to_arr(t_filler *info)
{
	size_t	pos;

	info->arr_stock = ft_strsplit(info->stock, '\n');
	if (info->arr_stock == NULL)
		return (MALLOC_FAIL);
	reallign_board(info);
	pos = 0;
	while (info->arr_stock[pos] != NULL && ft_strstr(info->arr_stock[pos], "Plateau ") == NULL)
		pos++;
	if (info->arr_stock[pos + 2] != NULL)
		info->arr_b = &(info->arr_stock[pos + 2]);
	while (info->arr_stock[pos] != NULL && ft_strstr(info->arr_stock[pos], "Piece ") == NULL)
		pos++;
	if (info->arr_stock[pos + 1] != NULL)
		info->arr_p = &(info->arr_stock[pos + 1]);
	return (0);
}

void	print_alloc(t_filler *info)
{
	int	i;

	i = 0;
	while (info->arr_stock[i] != NULL)
	{
		ft_dprintf(info->fd_debug, "%s\n", info->arr_stock[i]);
		i++;
	}
	i = 0;
	ft_dprintf(info->fd_debug, "|||||||||\n");
	while (i < info->line_b)
	{
		ft_dprintf(info->fd_debug, "%s\n", info->arr_b[i]);
		i++;
	}
	i = 0;
	ft_dprintf(info->fd_debug, "|||||||||\n");
	while (i < info->line_p)
	{
		ft_dprintf(info->fd_debug, "%s\n", info->arr_p[i]);
		i++;
	}
}

int		parse(t_filler *info, int turn)
{
	int		ret;

	ret = read_to_str(info);
	if (ret == READ_ERROR)
		return (READ_ERROR);
	ret = str_to_arr(info);
	ret = check_arr(info, turn);
	if (ret != STR_OK)
		return (READ_ERROR);
	//ft_dprintf(info->fd_debug, "%sI am %s\nOp is %s\n",info->stock,  info->piece_id, info->piece_id_op);
	//ft_dprintf(info->fd_debug, "lne_b = %i\ncol_b = %i\n", info->line_b, info->column_b);
	//ft_dprintf(info->fd_debug, "line_p = %i\ncolumn_p = %i\n", info->line_p, info->column_p);
	print_alloc(info);
	return (0);
}
