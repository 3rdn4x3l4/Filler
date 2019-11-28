#ifndef	FILLER_H
# define FILLER_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

# define BUFF_SIZE 100

#define NO_PLAYER 128
#define PLAYER_OK 127
#define BOARD_ERROR 126
#define BOARD_OK 125
#define PIECE_ERROR 124
#define PIECE_OK 123
#define STR_OK 122
#define READ_ERROR 121
#define INVALID_INFO 120
#define NL_ERROR 119
#define NL_OK 118

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
	int		fd_debug;
}					t_filler;

int					read_to_str(t_filler *info, int turn);
void				clean_alloc(t_filler *info, int code);
int					can_fetch_nbr(char const * const str);
int					board_content(t_filler *info);
int 				piece_content(t_filler *info);
#endif
