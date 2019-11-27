#include "filler.h"
#include "libft/includes/libft.h"
#include "libft/includes/get_next_line.h"
#include "libft/includes/ft_printf.h"

void	clean_board(t_filler *info)
{
	int	line_count;

	line_count = 0;
	while (info->arr_b[line_count])
	{
		free(info->arr_b[line_count]);
		line_count++;
	}
	free(info->arr_b);
}

void	clean_piece(t_filler *info)
{
	int	line_count;

	line_count = 0;
	while (info->arr_p[line_count])
	{
		free(info->arr_p[line_count]);
		line_count++;
	}
	free(info->arr_p);
}

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
