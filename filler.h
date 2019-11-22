#ifndef	FILLER_H
# define FILLER_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct		s_filler
{
	char	**board;
	char 	**piece;
	char	*piece_id;
	char	*piece_id_op;
	int		b_line;
	int		b_column;
	int		p_line;
	int		p_column;
	int		init_X;
	int		init_Y;
	int		init_op_X;
	int		init_op_Y;
}					t_filler;

void	read_board(t_filler *info, int fd);
void	read_piece(t_filler *info, int fd);
#endif
