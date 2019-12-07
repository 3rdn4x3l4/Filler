#include "filler.h"
#include "libft/includes/libft.h"
#include "libft/includes/get_next_line.h"
#include "libft/includes/ft_printf.h"
#include <fcntl.h>

/*
** 1) Start
** Prog reads on standard input the player order like so:
** $$$ exec p1 : [player name]
** $$$ exec p2 : [palyer name]
**
** p1 is identified by 'o' 'O'
** p2 is identified by 'x' 'X'
**
**
** 2) Read board and piece
** Prog reads the game board like so:

each turn:

Plateau Lne 14  Col 30:
    01234567890134567890123456789
000 .............................
001 .............................
002 ..X..........................
003 .............................
004 .............................
005 .............................
006 .............................
007 .............................
008 .............................
009 .............................
010 .............................
011 ..........................O..
012 .............................
013 .............................
Piece Lne 4 Col 7:
...*...
...*...
...*...
..***..

map02 is 100x99:
(info->column_b + 5) * (info->line_b + 1)
board_len = (99 + 5) * (100 + 1) = 104 * 101 = 10504
piece_len = (99 + 1) * (100) = 100 * 100 =  10000
player_len = 60
max read = brd + plyr + pce = 20504;

**
** Prog places piece by giving where the top left of the piece should be placed in the board coordinates system.
** In the example player X can place the piece by printing 2 -1
*/

void		print_boards(t_filler *info)
{
	int lne = 0;
	while (lne < info->line_b)
	{
		ft_dprintf(info->fd_debug, "|%.100s|\n", info->column_b);
		lne++;
	}
	lne = 0;
	while (lne < info->line_p)
	{
		ft_dprintf(info->fd_debug, "|%.100s|\n", info->column_p);
		lne++;
	}
}

void free_alloc(int ret, t_filler *info)
{
	int lne = 0;
	(void)ret;
	while (lne < info->line_b)
	{
		free(info->arr_b[lne]);
		lne++;
	}
	while (lne < info->line_p)
	{
		free(info->arr_p[lne]);
		lne++;
	}
}

int			main(void)
{
	int			ret;
	char		turn;
	t_filler	info;

	ft_bzero(&info, sizeof(info));
	info.fd_debug = open("output.txt", O_CREAT|O_RDWR|O_APPEND);
	turn = 0;
	while (1)
	{
		ret = parse(&info, turn);
		turn++;
		if (ret != 0)
			return (EXIT_FAILURE);
		print_boards(&info);
		//find_move(info);
		//play_move(info);
		free_alloc(ret, &info);
		close(info.fd_debug);
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
