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

/*
** 1) parser to read:
** - board and piece
** 2) best pos to know coor
** - then write coor
*/

int			main(void)
{
	int			fd_debug;
	t_filler	info;

	fd_debug = open("output.txt", O_CREAT|O_RDWR|O_APPEND);
	get_infos(fd_debug, &info);
	get_init_pos(&info);
	dprintf(fd_debug, "|X %i||Y %i||Xop %i||Yop %i|", info.init_X, info.init_Y, info.init_op_X, info.init_op_Y);
	close(fd_debug);
	ft_printf("8 2\n");
	return (0);
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
** Plateau Lne 14  Col 30:
**     01234567890134567890123456789
** 000 .............................
** 001 .............................
** 002 ..X..........................
** 003 .............................
** 004 .............................
** 005 .............................
** 006 .............................
** 007 .............................
** 008 .............................
** 009 .............................
** 010 .............................
** 011 ..........................O..
** 012 .............................
** 013 .............................
**
** 
** Prog reads the pieces like so:
** Piece Lne 4 Col 7:
**  ...*...
**  ...*...
**  ...*...
**  ..***..
**
** Each turn Prog reads the updated map and the piece to place.
**
** Prog places piece by giving where the top left of the piece should be placed in the board coordinates system.
** In the example player X can place the piece by printing 2 -1
**
** After printing on the output, Prog is stopped until next turn by vm.
*/


