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

/*
 * check if Board is OK
*/
int		board_info(t_filler *info)
{
	if (info->pos == NULL)
		return (BOARD_ERROR);
	if (can_fetch_nbr(info->pos) == FALSE)
		return (BOARD_ERROR);
	info->line_b = atoi(info->pos + 7);
	info->column_b = atoi(ft_strchr(info->pos + 8, ' '));
	if (board_content(info) == BOARD_ERROR)
		return (BOARD_ERROR);
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
	if (piece_content(info) == PIECE_ERROR)
		return (PIECE_ERROR);
	return (PIECE_OK);
}

int		get_str_info(t_filler *info, int turn)
{
	int ret;

	ret = player_info(info, turn);
	if (ret == NO_PLAYER)
		return (ret);
	info->pos = ft_strstr(info->stock, "Plateau ");
	ret = board_info(info);
	if (ret == BOARD_ERROR)
		return (ret);
	ft_dprintf(info->fd_debug, "|||||||||||\n");
	info->pos = ft_strstr(info->pos, "Piece ");
	ret = piece_info(info);
	if (ret == PIECE_ERROR)
		return (ret);
	return (STR_OK);
}

int		read_to_str(t_filler *info, int turn)
{
	char	buff[BUFF_SIZE + 1];
	int		ret;

	while ((ret = read(0, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (info->stock == NULL)
			info->stock = ft_strdup(buff);
		else
			info->stock = ft_strjoinfree(info->stock, buff, 1);
	}
	if (ret == -1)
		return (READ_ERROR);
	ret = get_str_info(info, turn);
	//ft_dprintf(info->fd_debug, "%sI am %s\nOp is %s\n",info->stock,  info->piece_id, info->piece_id_op);
	ft_dprintf(info->fd_debug, "lne_b = %i\ncol_b = %i\n", info->line_b, info->column_b);
	ft_dprintf(info->fd_debug, "line_p = %i\ncolumn_p = %i\n", info->line_p, info->column_p);
	free(info->stock);
	if (ret != STR_OK)
		return (INVALID_INFO);
	return (ret);
}
