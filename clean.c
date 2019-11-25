#include "filler.h"
#include "libft/includes/libft.h"
#include "libft/includes/get_next_line.h"
#include "libft/includes/ft_printf.h"

/*use code to determine what to free*/
/* -1 == no Board alloc*/
/* -2 == no Piece alloc*/
/* -3 == B and P alloc*/
void	clean_alloc(t_filler *info, int code)
{
	if (code <= -2)
		clean_board(info);
	if (code == -3)
		clean_piece(info);
}

void	clean_board(t_filler *info)
{
	int	line_count;

	line_count = 0;
	while (info->board[line_count])
	{
		free(info->board[line_count]);
		line_count++;
	}
	free(info->board);
}

void	clean_piece(t_filler *info)
{
	int	line_count;

	line_count = 0;
	while (info->piece[line_count])
	{
		free(info->piece[line_count]);
		line_count++;
	}
	free(info->piece);
}
