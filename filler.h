#ifndef	FILLER_H
# define FILLER_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

# define BUFF_SIZE 100

typedef struct		s_filler
{
	char 	**arr_p;
	char	**arr_b;
	char	*piece_id;
	char	*piece_id_op;
	int		line_p;
	int		column_p;
	int		line_b;
	int		column_b;
}					t_filler;

int					read_info(t_filler *info, int fd);
void				clean_alloc(t_filler *info, int code);
#endif
