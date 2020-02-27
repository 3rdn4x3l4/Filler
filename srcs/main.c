/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:13:03 by alagache          #+#    #+#             */
/*   Updated: 2020/02/27 14:28:59 by alagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include "ft_printf.h"
#include <fcntl.h>

int			main(void)
{
	int			ret;
	int			turn;
	t_filler	info;

	ft_bzero(&info, sizeof(info));
	turn = 0;
	info.fd = open("output.txt", O_RDWR | O_TRUNC);
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
	close(info.fd);
	return (EXIT_SUCCESS);
}
