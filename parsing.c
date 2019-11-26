#include "libft/includes/ft_printf.h"
//my printf lib
#include <unistd.h>
//write read
#include <stdlib.h>
//malloc
#include <stdio.h>
//perror
#include <string.h>
//strerror
#include "filler.h"
#include "libft/includes/libft.h"
#include "libft/includes/get_next_line.h"

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

int			read_info(t_filler *info, int fd)
{
	read_board(info, fd);
	if (info->board == NULL)
		return (-1);
	read_piece(info, fd);
	if (info->piece == NULL)
		return (-2);
	//check_info();
	return (0);
}
