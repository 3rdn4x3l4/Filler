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

int	is_map(char c)
{
	if (ft_strchr(".XxOo", c) == NULL)
		return (FALSE);
	return (TRUE);
}

int	is_piece(char c)
{
	if (ft_strchr(".*", c) == NULL)
		return (FALSE);
	return (TRUE);
}
