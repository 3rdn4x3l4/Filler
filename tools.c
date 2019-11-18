#include "libft/includes/ft_printf.h"
//my printf lib
#include <unistd.h>
//write read
#include <stdlib.h>
//malloc
#include <stdio.h>
//perror
#include <string.h>
//strerror
#include "filler.h"
#include "libft/includes/libft.h"
#include "libft/includes/get_next_line.h"
#include <fcntl.h>

void		get_init_pos(t_filler *info)
{
	int 	c;
	char 	*pos;


	info->piece_id_op = (ft_strcmp(info->piece_id, "O") == 0) ? "X" : "O";
	c = 0;
	while (c < info->line)
	{
		if ((pos = ft_strstr(info->board[c], info->piece_id)) != NULL)
		{
			info->init_X = c;
			info->init_Y = (int)(pos - info->board[c]);
		}
		c++;
	}
	c = 0;
	while (c < info->line)
	{
		if ((pos = ft_strstr(info->board[c], info->piece_id_op)) != NULL)
		{
			info->init_op_X = c;
			info->init_op_Y = (int)(pos - info->board[c]);
		}
		c++;
	}
}

int			get_piece_size(t_filler *info)
{
	int x;
	int y;
	int size;

	x = 0;
	y = 0;
	size = 0;
	while (info->piece[x] != '\0')
	{
		while (info->piece[x][y] != '\0')
		{
			if (info->piece[x][y] != '.')
				size++;
			y++;
		}
		x++;
	}
	return (size);
}
