#ifndef	FILLER_H
# define FILLER_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

# define BUFF_SIZE 100
# define MAX_LEN 20504
# define READ_ERROR 128
# define ARR_MALLOC 128
# define ARR_ERROR 128
# define STR_ERROR 128
# define ERROR 128
# define ARR1 128
# define ARR2 128
# define ERR_MAP 128
# define ERR_SHAPE 128

typedef struct		s_filler
{
	short	**map;
	short	**shape;
	char	**board;
	char 	**piece;
	char	**arr;
	char	*stock;
	char	id[2];
	char	id_op[2];
	int		b_line;
	int		b_column;
	int		p_line;
	int		p_column;
}					t_filler;

int					parse(t_filler *info, int turn);
void				free_arr(void **arr);
#endif
