#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "filler.h"
#include "libft/includes/libft.h"
#include "libft/includes/ft_printf.h"

int	can_fetch_nbr(char const *const str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalpha(str[i]) == TRUE || str[i] == ' '))
		i++;
	while (str[i] && ft_isdigit(str[i]) == TRUE)
		i++;
	if (str[i] && str[i] == ' ')
		i++;
	while (str[i] && ft_isdigit(str[i]) == TRUE)
		i++;
	if (str[i] && str + i == ft_strchr(str, ':'))
		return (TRUE);
	return (FALSE);
}

//check each NL 
int	check_newlines(char const *const str, int line, int column, int fd, int offset)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while (str[pos] && str[pos] == '\n')
	{
		pos = ++i * (column + 1 + offset);
	}
	ft_dprintf(fd, "final i = |%i| && line = |%i|\n", i - 1, line);
	if (line == i - 1)
		return (NL_OK);
	return (NL_ERROR);
}

int	map_part(char const *str, t_filler *info)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		i++;
	}
	ft_dprintf(info->fd_debug, "i = %i\n");
	return (BOARD_OK);
}

int	first_line_offset(char const *str, t_filler *info)
{
	int	i;
	int	line;

	i = 1;
	while (str[i] && (ft_isdigit(str[i]) == TRUE || str[i] == ' '))
		i++;
	if (str[i] != '\n')
		return (BOARD_ERROR);
	str += i;
	line = 1;
	while (line < info->line_b + 1)
	{
		i = 1;
		while (i < 5)
		{
			if (str[i] && ft_isdigit(str[i]) == FALSE && str[i] != ' ')
				return (BOARD_ERROR);
			i++;
		}
		if (map_part(str + i - 1, info) == BOARD_ERROR)
			return (BOARD_ERROR);
		line++;
	}
	return (BOARD_OK);
}

int	board_content(t_filler *info)
{
	char	*str;
	int		ret;

	str = ft_strchr(info->pos, '\n');
	ret = check_newlines(str, info->line_b + 1, info->column_b, info->fd_debug, 4);
	if (ret == NL_ERROR)
		return (BOARD_ERROR);
	ret = first_line_offset(str, info);
	if (ret == BOARD_ERROR)
		return (BOARD_ERROR);
	return (BOARD_OK);
}

int piece_content(t_filler *info)
{
	char	*str;
	int		ret;

	str = ft_strchr(info->pos, '\n');
	ret = check_newlines(str, info->line_p, info->column_p, info->fd_debug, 0);
	if (ret == NL_ERROR)
		return (PIECE_ERROR);
	return (PIECE_OK);
}
