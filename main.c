#include "filler.h"
#include "libft/includes/libft.h"
#include "libft/includes/get_next_line.h"
#include "libft/includes/ft_printf.h"
#include <fcntl.h>

void	init_struct(t_filler *info, int fd)
{
	char	*ptr;
	char	*line;
	int 	ret;

	ret = get_next_line(0, &line);
	if (ret != -1)
	{
		ptr = ft_strchr(line, 'p');
		if (ptr != NULL)
			info->piece_id = (ptr[1] == '1') ? "Oo" : "Xx";
		free(line);
	}
	(void)fd;
	/*ft_dprintf(fd, "line:\n%s\nPlayer identifier is %s\n", line, info->piece_id);*/
}

int			main(void)
{
	int			fd_debug;
	int			ret;
	t_filler	info;

	fd_debug = open("output.txt", O_CREAT|O_RDWR|O_APPEND);
	ft_bzero(&info, sizeof(info));
	init_struct(&info, fd_debug);
	if (info.piece_id == '\0')
		return (EXIT_FAILURE);
	while (1)
	{
		/*read_info (calls read_board/piece) return -1/-2 if alloc fails then calls clean_alloc with code to clean b and p or b*/
		ret = read_info(&info, fd_debug);
		if (ret != 0)
		{
			clean_alloc(&info, ret);
			return (EXIT_FAILURE);
		}
		/*play_turn(&info);
		clean_alloc(&info, -3);*/
		close(fd_debug);
		ft_printf("12 14\n");
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
