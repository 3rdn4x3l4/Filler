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

**
** Prog places piece by giving where the top left of the piece should be placed in the board coordinates system.
** In the example player X can place the piece by printing 2 -1
*/


int			main(void)
{
	int			fd_debug;
	int			ret;
	char		turn;
	t_filler	info;

	fd_debug = open("output.txt", O_CREAT|O_RDWR|O_APPEND);
	ft_bzero(&info, sizeof(info));
	turn = 0;
	while (1)
	{
		/*read_info (calls read_board/piece) return -1/-2 if alloc fails then calls clean_alloc with code to clean b and p or b*/
		ret = read_info(&info, fd_debug, turn);
		turn = 1;
		if (ret != 0)
		{
			clean_alloc(&info, ret);
			return (EXIT_FAILURE);
		}
		close(fd_debug);
		ft_printf("12 14\n");
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
