#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "filler.h"
#include "libft/includes/libft.h"
#include "libft/includes/ft_printf.h"

int	is_piece(char c)
{
	if (ft_strchr(".*", c) == NULL)
		return (FALSE);
	return (TRUE);
}

int piece_content(t_filler *info)
{
	char	*str;
	char	*ptr;
	int		col;
	int		lne;

	str = ft_strchr(info->pos, '\n');
	ptr = str + 1;
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
		if ('\n' != ptr[lne * (info->column_p + 1) + col + 1])
			return (PIECE_ERROR);
		lne++;
	}
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
