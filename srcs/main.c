/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <alagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 15:56:19 by alagache          #+#    #+#             */
/*   Updated: 2020/04/20 13:49:11 by alagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdlib.h>

int			main(void)
{
	int			ret;
	int			turn;
	t_filler	info;

	ft_bzero(&info, sizeof(info));
	turn = 0;
	while (1 && turn != -1)
	{
		ret = parse(&info, turn);
		if (ret != SUCCESS)
			return (EXIT_FAILURE);
		if (info.play == -1)
			return (EXIT_SUCCESS);
		clean_struct(&info);
		turn++;
	}
	return (EXIT_SUCCESS);
}
