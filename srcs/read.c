/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <alagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 15:56:43 by alagache          #+#    #+#             */
/*   Updated: 2020/04/16 13:06:06 by alagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	check_read(char *str, int len)
{
	int	i;

	i = -1;
	str[len] = '\0';
	if (ft_strstr(str, "#!/") != NULL)
		return (FAILURE);
	while (++i < len)
	{
		if (str[i] <= 0)
			return (FAILURE);
	}
	return (SUCCESS);
}
