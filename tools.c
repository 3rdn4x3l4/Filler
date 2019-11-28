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

	while (i < line + 1)
	{
		pos = i * (column + 1 + offset);
		if (str[pos] && str[pos] != '\n')
			return (NL_ERROR);
		i++;
	}
	ft_dprintf(fd, "(i = %i |%.1s|)", i - 1, str + pos);
	return (NL_OK);
}

int	board_content(t_filler *info)
{
	char	*str;
	int		ret;
	int		offset;

	str = ft_strchr(info->pos, '\n');
	offset = 0;
	while (str[offset + 1] && str[offset + 1] == ' ')
		offset++;
	ret = check_newlines(str, info->line_b, info->column_b, info->fd_debug, offset);
	if (ret == NL_ERROR)
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
