#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "filler.h"
#include "libft.h"
#include "ft_printf.h"

//int		player_info(t_filler *info, int turn)
//{
//	if (turn != 0)
//		return (PLAYER_OK);
//	if (ft_strnstr(info->stock, "$$$ exec p", 10) == NULL)
//		return (NO_PLAYER);
//	info->piece_id = (info->stock[10] == 1) ? "Oo" : "Xx";
//	info->piece_id_op = (ft_strcmp(info->piece_id, "Oo") == 0) ? "Xx" : "Oo";
//	return (PLAYER_OK);
//}

//int		board_info(t_filler *info)
//{
//	//int ret;
//
//	if (info->pos == NULL)
//		return (BOARD_ERROR);
//	if (can_fetch_nbr(info->pos) == FALSE)
//		return (BOARD_ERROR);
//	info->line_b = atoi(info->pos + 7);
//	info->column_b = atoi(ft_strchr(info->pos + 8, ' '));
//	//ret = board_content(info);
//	//if (ret == BOARD_ERROR)
//	//	return (BOARD_ERROR);
//	return (BOARD_OK);
//}

//int		piece_info(t_filler *info)
//{
//	if (info->pos == NULL)
//		return (PIECE_ERROR);
//	if (can_fetch_nbr(info->pos) == FALSE)
//		return (PIECE_ERROR);
//	info->line_p = atoi(info->pos + 6);
//	info->column_p = atoi(ft_strchr(info->pos + 7, ' '));
//	//if (piece_content(info) == PIECE_ERROR)
//	//	return (PIECE_ERROR);
//	return (PIECE_OK);
//}

int		read_to_str(t_filler *info)
{
	char	*str;
	char	buff[BUFF_SIZE + 1];
	int		ret;
	size_t	len;

	len = 0;
	str = ft_strnew(0);
	if (str == NULL)
		return (STR_ERROR);
	while ((ret = read(0, buff, BUFF_SIZE)) > 0 && (len += ret) <= MAX_LEN)
	{
		buff[ret] = '\0';
		str = ft_strjoinfree(str, buff, 1);
	}
	if (len > MAX_LEN || ret == -1)
	{
		if (str != NULL)
			free(str);
		return (READ_ERROR);
	}
	info->stock = str;
	return(0);
}

int		str_to_arr(t_filler *info)
{
	info->arr = ft_strsplit(info->stock, '\n');
	if (info->arr == NULL)
		return (ARR_MALLOC);
	free(info->stock);
	return (0);
}

/* use real indices instead of moving ptr and use the arr board
void		reallign_board(t_filler *info)
{
	char	**arr;
	int		len;

	arr = info->arr;
	while (*arr != NULL && ft_strcmp(*arr, "000 ") != 0)
		arr++;
	len = ft_strlen(*arr);
	while (ft_strcmp(*arr, "Piece ") != 0)
	{
		ft_memmove(*arr, (*arr) + 4, len - 4);
		arr++;
	}
}

*/
void	init_ptrs(t_filler *info)
{
	int	i;

	i = 0;
	while (info->arr[i] != NULL && ft_strncmp(info->arr[i], "Plateau ", 8) != 0)
		i++;
	info->board = ft_strsplit();
	while (info->arr[i] != NULL && ft_strncmp(info->arr[i], "Piece ", 6) != 0)
		i++;
	info->piece = ft_strsplit();
}

/*
int		get_board_size()
{
}

int		get_piece_rsize()
{
}

int		get_piece_offset()
{
}

void	fill_heatmap()
{
}

int		get_best_pos()
{
}

int		print_best_pos()
{
}
*/

void	print_alloc(t_filler *info)
{
	int	i;

	i = 0;
	while (info->arr[i] != NULL)
	{
		printf("%s\n", info->arr[i]);
		i++;
	}
	i = 0;
	printf("|||||||||\n");
	while (ft_strstr(info->board[i], "Piece") == NULL)
	{
		printf("%s\n", info->board[i]);
		i++;
	}
	i = 0;
	printf("|||||||||\n");
	while (info->piece[i] != NULL)
	{
		printf("%s\n", info->piece[i]);
		i++;
	}
}

int		parse(t_filler *info, int turn)
{
	int		ret;

	ret = read_to_str(info);
	if (ret == STR_ERROR || ret == READ_ERROR)
		return (ERROR);
	ret = str_to_arr(info);
	if (ret == ARR_ERROR)
		return (ERROR);
	init_ptrs(info);
	//reallign_board(info);
	print_alloc(info);
	turn++;
	//get_board_size();
	//get_piece_rsize();
	//get_piece_offset();
	//fill_heatmap();
	//get_best_pos();
	//print_best_pos();
	return (0);
}
