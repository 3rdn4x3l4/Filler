#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "filler.h"
#include "libft/includes/libft.h"
#include "libft/includes/ft_printf.h"

int	board_exist(t_filler *info, char *ptr)
{
	char *tmp;

	tmp = ptr;
	while (ft_strchr(" 0123456789.XxOo\n", *ptr) != NULL)
		ptr++;
	if (ptr != ft_strstr(info->stock, "Piece"))
		return (FALSE);
	if ((int)(ptr - tmp) != (info->column_b + 5) * (info->line_b + 1))
		return (FALSE);
	return (TRUE);
}

int board_content(t_filler *info)
{
	char	*str;
	char	*ptr;
	int		col;
	int		lne;

	str = ft_strchr(info->pos, '\n');
	ptr = str + 1;
	if (board_exist(info, ptr) == FALSE)
		return (BOARD_ERROR);
	ptr += (5 + info->column_b);
	lne = 0;
	while (lne < info->line_b)
	{
		col = 4;
		while (col - 4 < info->column_b)
		{
			if (is_map(ptr[lne * (info->column_b + 1) + col]) == FALSE)
				return (BOARD_ERROR);
			col++;
		}
		ft_dprintf(info->fd_debug, "||BC line %i OK||\n", lne);
		//ft_dprintf(info->fd_debug, "|%c|\n", ptr[lne * (info->column_b + 1) + col]);
		if ('\n' != ptr[lne * (info->column_b + 1) + col])
			return (BOARD_ERROR);
		ft_dprintf(info->fd_debug, "||NL line %i OK||\n", lne);
		lne++;
	}
	return (BOARD_OK);
}

int piece_content(t_filler *info)
{
	char	*str;
	char	*ptr;
	int		col;
	int		lne;

	str = ft_strchr(info->pos, '\n');
	ptr = str + 1;
	lne = 0;
	while (lne < info->line_p)
	{
		col = 0;
		while (col < info->column_p)
		{
			if (is_piece(ptr[lne * (info->column_p + 1) + col]) == FALSE)
				return (PIECE_ERROR);
			col++;
		}
		if ('\n' != ptr[lne * (info->column_p + 1) + col])
			return (PIECE_ERROR);
		lne++;
	}
	return (PIECE_OK);
}
	/*
	while (is_piece(*ptr) == TRUE)
		ptr++;
	if (ptr != NULL)
		return (PIECE_ERROR);
	ptr--;
	while (*ptr == '\n' && ptr - str > 0)
		ptr -= info->column_p + 1;
	return (PIECE_OK);
	*/
