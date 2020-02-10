#include "filler.h"
#include "libft.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include <fcntl.h>

int			main(void)
{
	int			ret;
	int			turn;
	t_filler	info;

	ft_bzero(&info, sizeof(info));
	turn = 0;
	while (1)
	{
		ret = parse(&info, turn);
		if (ret != 0)
			return (EXIT_FAILURE);
		//play_move(&info);
		free_arr((void**)info.arr);
		turn++;
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}


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
ft_memmove
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
** Prog places piece by giving where the top left of the piece should be placed in the board coordinates system (Lne Col order)
** In the example player X can place the piece by printing 2 -1
*/
