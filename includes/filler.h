/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:11:28 by alagache          #+#    #+#             */
/*   Updated: 2020/02/21 16:02:35 by alagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>

# define SUCCESS 0
# define FAILURE 1
# define BUFF_SIZE 4096
# define MAX_LEN 20504
# define OP_VALUE -2
# define MY_VALUE -1
# define PIECE_VALUE -3
# define READ_ERROR 128
# define ARR_MALLOC 128
# define ARR_ERROR 128
# define STR_ERROR 128
# define ERROR 128
# define ARR1 128
# define ARR2 128
# define ERR_MAP 128
# define ERR_SHAPE 128

typedef struct		s_filler
{
	short	**map;
	short	**shape;
	char	**board;
	char	**piece;
	char	**arr;
	char	*stock;
	char	id[2];
	char	id_op[2];
	int		b_line;
	int		b_column;
	int		p_line;
	int		p_column;
	int		lne_offset;
	int		col_offset;
	int		heatscore;
	int		best_lne;
	int		best_col;
	int		fd;
}					t_filler;

int					parse(t_filler *info, int turn);
void				free_arr(void **arr);
int					get_arrs(t_filler *info, int turn);
int					is_placable(t_filler *info, int lne, int col);
int					get_heat_score(t_filler *info, int lne, int col);
void				play_best_move(t_filler *info);
void				print_shape(t_filler *info);
void				print_map(t_filler *info);
void				get_sizes(t_filler *info);
void				init_ptrs(t_filler *info);
int					create_arrs(t_filler *info);
int					fill_map_arr(t_filler *info);
int					fill_shape_arr(t_filler *info);
void				fill_heatmap(t_filler *info);
void				get_piece_offset(t_filler *info);
void				effective_piece_size(t_filler *info);

#endif
