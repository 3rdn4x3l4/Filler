#ifndef	FILLER_H
# define FILLER_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

# define BUFF_SIZE 100

typedef struct		s_filler
{
	char	**arr_b;
	char 	**arr_p;
	char	*stock;
	char	*pos;
	char	*piece_id;
	char	*piece_id_op;
	int		line_b;
	int		column_b;
	int		line_p;
	int		column_p;
}					t_filler;

int					read_info(t_filler *info, int fd, int turn);
void				clean_alloc(t_filler *info, int code);
void				init_struct(t_filler *info, int fd);
#endif
