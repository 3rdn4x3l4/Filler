#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "filler.h"
#include "libft/includes/libft.h"
#include "libft/includes/ft_printf.h"

/*
void		b_line_col(t_filler *info, char *str)
{
	int c;

	c = 7;
	while (ft_isdigit(str[c]) == 0)
		c++;
	info->b_line = atoi(str + c);
	while (ft_isdigit(str[c]) == 1)
		c++;
	info->b_column = atoi(str + c);
	free(str);
}

void	read_board(t_filler *info, int fd)
{
	char	*line;
	int		ret;
	int		line_count;

	ret = get_next_line(0, &line);
	if (ret != -1)
		b_line_col(info, line);
	ret = get_next_line(0, &line);
	if (ret != -1)
		free(line);
	line_count = 0;
	info->board = ft_memalloc(sizeof(char*) * (info->b_line + 1));
	if (info->board != NULL)
	{
		while (line_count < info->b_line && (ret = get_next_line(0, &line) > 0))
		{
			info->board[info->b_line] = ft_strsub(line, ft_strlen(line) - info->b_column, info->b_column);
			free(line);
			line_count++;
		}
		(void)fd;
	}
}

void		p_line_col(t_filler *info, char *str)
{
	int c;

	c = 5;
	while (ft_isdigit(str[c]) == 0)
		c++;
	info->p_line = atoi(str + c);
	while (ft_isdigit(str[c]) == 1)
		c++;
	info->p_column = atoi(str + c);
	free(str);
}

void	read_piece(t_filler *info, int fd)
{
	char	*line;
	int		ret;
	int		line_count;

	ret = get_next_line(0, &line);
	if (ret != -1)
		p_line_col(info, line);
	line_count = 0;
	info->piece = ft_memalloc(sizeof(char*) * (info->p_line + 1));
	if (info->piece != NULL)
	{
		while (line_count < info->p_line && (ret = get_next_line(0, &line) > 0))
		{
			info->piece[info->p_line] = line;
			line_count++;
		}
		(void)fd;
	}
}
*/
#define NO_PLAYER 128
#define NOTHING 127
#define DONE 126
#define B_ALLOC_FAIL 125
#define BOARD_ERROR 124
#define P_ALLOC_FAIL 123
#define PIECE_ERROR 122

/*
 * if first turn and has palyer info
 * init piece_id with the player charset
 * else do nothing
*/
int		get_player(t_filler *info, int turn)
{
	if (turn != 0)
		return (DONE);
	if (ft_strnstr(info->stock, "$$$ exec p", 10) == NULL)
		return (NO_PLAYER);
	info->piece_id = (info->stock[10] == 1) ? "Oo" : "Xx";
	info->piece_id_op = (ft_strcmp(info->piece_id, "Oo") == 0) ? "Xx" : "Oo";
	return (DONE);
}

/*
 * check if Board is OK then
 * Alloc arr of line + 1 elements
*/
int		get_board(t_filler *info)
{
	info->pos = ft_strchr(info->stock, '\n');
	if (info->pos == NULL)
		return (BOARD_ERROR);
	info->pos = ft_strstr(info->pos, "Plateau ");
	if (info->pos == NULL)
		return (BOARD_ERROR);
	info->line_b = atoi(info->pos + 7);
	info->column_b = atoi(ft_strchr(info->pos + 8, ' '));
	while (info->pos != NULL && *(info->pos) != '\n')
		info->pos++;
	return (0);
}

int		get_piece(t_filler *info)
{
	info->pos = ft_strstr(info->pos, "Piece ");
		return (PIECE_ERROR);
	info->pos = ft_strstr(info->pos, "Plateau ");
	if (info->pos == NULL)
		return (PIECE_ERROR);
	info->line_b = atoi(info->pos + 7);
	info->column_b = atoi(ft_strchr(info->pos + 8, ' '));
}

int		read_info(t_filler *info, int fd, int turn)
{
	char	buff[BUFF_SIZE + 1];
	int		ret;

	while ((ret = read(0, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (info->stock == NULL)
			info->stock = ft_strdup(buff);
		else
			info->stock = ft_strjoinfree(info->stock, buff, 1);
	}
	if (ret == -1)
		return (-1);
	(void)turn;
	ret = get_player(info, turn);
	if (ret == NO_PLAYER)
		return (ret);
	ret = get_board(info);
	if (ret == B_ALLOC_FAIL || ret == BOARD_ERROR)
		return (ret);
	ret = get_piece(info);
	if (ret == P_ALLOC_FAIL || ret == PIECE_ERROR)
		return (ret);
	ft_dprintf(fd, "%sI am %s\nOp is %s\nline_b = %i\ncolumn_b = %i\n", info->stock,  info->piece_id, info->piece_id_op, info->line_b, info->column_b);
	ft_dprintf(fd, "|%.1s|\n", info->stock);
	ft_dprintf(fd, "line_p = %i\ncolumn_p = %i\n", info->line_p, info->column_p);
	/*
	if (get_piece(info) == -1)
		return ();
	*/
	//check_info();
	free(info->stock);
	return (0);
}
