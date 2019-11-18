#ifndef	FILLER_H
# define FILLER_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct		s_filler
{
	char	**board;
	int		line;
	int		column;
	int		init_X;
	int		init_Y;
	int		init_op_X;
	int		init_op_Y;
	char 	**piece;
	int		piece_line;
	int		piece_column;
	char	*piece_id;
	char	*piece_id_op;
}					t_filler;


void				get_line_col(t_filler *info, char *str);
int					get_board(t_filler *info);
void				get_piece_line_col(t_filler *info, char *str);
int					get_piece(t_filler *info);
void				get_infos(int fd, t_filler *info);
void				get_init_pos(t_filler *info);
int					get_piece_size(t_filler *info);
#endif
