/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagache <alagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 15:57:49 by alagache          #+#    #+#             */
/*   Updated: 2020/04/14 14:02:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# define SUCCESS 0
# define FAILURE 1
# define BUFF_SIZE 4096
# define OP_VALUE -2
# define MY_VALUE -1
# define PIECE_VALUE -3
# define READ_ERROR 128
# define ARR_MALLOC 128
# define STR_ERROR 128
# define ERROR 128
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
	int		b_line;
	int		b_column;
	int		p_line;
	int		p_column;
	int		lne_offset;
	int		col_offset;
	int		play;
	int		best_lne;
	int		best_col;
	int		fd;
	char	id[2];
	char	id_op[2];
}					t_filler;

int					parse(t_filler *info, int turn);
int					check_read(char *str, int len);
void				free_arr(void **arr);
int					get_arrs(t_filler *info, int turn);
int					is_placable(t_filler *info, int lne, int col);
int					get_heat_score(t_filler *info, int lne, int col);
void				get_sizes(t_filler *info);
int					check_sizes(t_filler *info);
void				init_ptrs(t_filler *info);
int					create_arrs(t_filler *info);
int					fill_map_arr(t_filler *info);
int					fill_shape_arr(t_filler *info);
void				fill_heatmap(t_filler *info);
void				get_piece_offset(t_filler *info);
void				effective_piece_size(t_filler *info);
void				free_allocs(t_filler *info);
void				clean_struct(t_filler *info);

#endif
