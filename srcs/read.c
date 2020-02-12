#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "filler.h"
#include "libft.h"
#include "ft_printf.h"

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

void	get_player_id(t_filler *info)
{
	if (info->arr[0][10] == '1')
	{
		info->id[0] = 'O';
		info->id[1] = 'o';
		info->id_op[0] = 'X';
		info->id_op[1] = 'x';
	}
	else
	{
		info->id_op[0] = 'O';
		info->id_op[1] = 'o';
		info->id[0] = 'X';
		info->id[1] = 'x';
	}
}

int		init_arrs(t_filler *info)
{
	int	i;

	i = 0;
	while (info->arr[i] != NULL && ft_strncmp(info->arr[i], "Plateau ", 8) != 0)
		i++;
	info->board = ft_strsplit(info->arr[i], ' ');
	if (info->board == NULL)
		return (ARR1);
	while (info->arr[i] != NULL && ft_strncmp(info->arr[i], "Piece ", 6) != 0)
		i++;
	info->piece = ft_strsplit(info->arr[i], ' ');
	if (info->piece == NULL)
		return (ARR2);
	return (0);
}

int		get_arrs(t_filler *info, int turn)
{
	int		ret;

	ret = read_to_str(info);
	if (ret == STR_ERROR || ret == READ_ERROR)
		return (ERROR);
	ret = str_to_arr(info);
	if (ret == ARR_ERROR)
		return (ERROR);
	if (turn == 0)
		get_player_id(info);
	ret = init_arrs(info);
	if (ret == ARR1)
		return (ERROR);
	else if (ret == ARR2)
	{
		free(info->board);
		return (ERROR);
	}
	return (0);
}

void	get_sizes(char **board, char **piece, t_filler *info)
{
	info->b_line = ft_atoi(board[1]);
	info->b_column = ft_atoi(board[2]);
	info->p_line = ft_atoi(piece[1]);
	info->p_column = ft_atoi(piece[2]);
}

/* get the sizes of the board and piece using board and piece arrays and free the arrays afterward*/
void	get_nbrs(t_filler *info)
{
	get_sizes(info->board, info->piece, info);
	free_arr((void**)info->board);
	free_arr((void**)info->piece);
}

void	init_ptrs(t_filler *info)
{
	int	i;

	i = 0;
	while (info->arr[i] != NULL && ft_strncmp(info->arr[i], "000 ", 4) != 0)
		i++;
	info->board = &(info->arr[i]);
	while (info->arr[i] != NULL && ft_strncmp(info->arr[i], "Piece ", 6) != 0)
		i++;
	info->piece = &(info->arr[i + 1]);
	//ft_printf("|init_ptrs|\n%s\n%s\n", *(info->board), *(info->piece));
}

int		create_arrs(t_filler *info)
{
	info->map = (short**)malloc(sizeof(short*) * (info->b_line + 1));
	if (info->map == NULL)
		return (ERR_MAP);
	info->shape = (short**)malloc(sizeof(short*) * (info->p_line + 1));
	if (info->shape == NULL)
	{
		free(info->map);
		return (ERR_SHAPE);
	}
	ft_memset(info->map, '\0', sizeof(short*) * (info->b_line + 1));
	ft_memset(info->shape, '\0', sizeof(short*) * (info->p_line + 1));
	return (0);
}

void	print_map(t_filler *info)
{
	int	i;
	int	j;

	i = 0;
	while (i < info->b_line)
	{
		j = 0;
		while (j < info->b_column)
		{
			printf("|%hi|", info->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	fill_map(char *str, short *line, const int size, t_filler *info)
{
	int	i;
	char	*op;

	op = info->id_op;
	i = 0;
	while (i < size)
	{
		/* pl_charset*/
		/* line[i] = (str[i] == op[0] || str[i] == op[1] ? OP_VALUE : MY_VALUE) */
		/* instead of if else if use this ternary operator */
		if (ft_strchr(info->id_op, str[i]) != NULL)
			line[i] = OP_VALUE;
		else if (ft_strchr(info->id, str[i]) != NULL)
			line[i] = MY_VALUE;
		i++;
	}
}

int		fill_map_arr(t_filler *info)
{
	int		i;
	int		size;

	i = 0;
	size = sizeof(short) * (info->b_column + 1);
	while (i < info->b_line)
	{
		info->map[i] = (short*)malloc(size);
		if (info->map[i] == NULL)
			return (ERROR);
		ft_memset(info->map[i], '\0', size);
		fill_map(info->board[i] + 4, info->map[i], info->b_column, info);
		i++;
	}
	print_map(info);
	return (0);
}
//shape
void	print_shape(t_filler *info)
{
	int	i;
	int	j;

	i = 0;
	while (i < info->p_line)
	{
		j = 0;
		while (j < info->p_column)
		{
			printf("|%hi|", info->shape[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	fill_shape(char *str, short *line, const int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (str[i] == '.')
			line[i] = 0;
		else
			line[i] = -3;
		i++;
	}
}

int		fill_shape_arr(t_filler *info)
{
	int		i;
	int		size;
		
	i = 0;
	size = sizeof(short) * (info->p_column + 1);
	while (i < info->p_line)
	{
		info->shape[i] = (short*)malloc(size);
		if (info->shape[i] == NULL)
			return (ERROR);
		ft_memset(info->shape[i], '\0', size);
		fill_shape(info->piece[i], info->shape[i], info->p_column);
		i++;
	}
	print_shape(info);
	return (0);
}
void	print_alloc(t_filler *info)
{
	int	i;

	i = 0;
	while (info->arr[i] != NULL)
	{
		//printf("%s\n", info->arr[i]);
		i++;
	}
	//printf("|||||\n");
	//printf("lne = %i\nCol = %i\n", info->b_line, info->b_column);
	//printf("lne = %i\nCol = %i\n", info->p_line, info->p_column);
}

/* fill the line of with values(incremental from the Opponent  from start to end,  */
void	fill_line(short *line, int start, int end, int direction)
{
	int	i;
	int	value;

	i = start;
	value = 1;
	while (i != end)
	{
		//if line[i] == MY_VALUE 
			//value++;
		//else if line[i] == OP_VALUE
			//value = 1;
		//else
		{
			//if line[i] == 0
			{
				//line[i] = value
				//value++
			}
			//else if value < line[i]
				//line[i] = value;
		}
		i += direction;
	}
}

/* fill_heatmap calls fill_line/fill_column to add increasing value from the positions of a char c*/
void	fill_heatmap(t_filler *info)
{
	circle_op();

}

int		parse(t_filler *info, int turn)
{
	int		ret;

	ret = get_arrs(info, turn);
	if (ret == ERROR)
		return (ERROR);
	get_nbrs(info);
	init_ptrs(info);
	create_arrs(info);
	fill_map_arr(info);
	fill_shape_arr(info);
	print_alloc(info);
	free_arr((void**)info->map);
	free_arr((void**)info->shape);
	turn++;
	//fill_heatmap();
	//get_best_pos();
	//print_best_pos();
	return (0);
}

/*
int		get_best_pos()
{
}

int		print_best_pos()
{
}
*/

