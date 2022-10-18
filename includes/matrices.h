/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:01:12 by thakala           #+#    #+#             */
/*   Updated: 2022/10/18 13:47:11 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MATRICES_H
# define MATRICES_H
# include "RTv1.h"

typedef struct s_index
{
	uint32_t	size;
	uint32_t	row;
	uint32_t	col;
}				t_index;

enum e_matrix_two_by_two_coordinates
{
	MATRIX_TWO_BY_TWO_ROW_0__COL_0,
	MATRIX_TWO_BY_TWO_ROW_0__COL_1,
	MATRIX_TWO_BY_TWO_ROW_1__COL_0,
	MATRIX_TWO_BY_TWO_ROW_1__COL_1
};

typedef struct s_twin_tuple {
	t_fl	col_0;
	t_fl	col_1;
}	t_twin_tuple;

typedef union u_wrap_matrix_two_by_two
{
	t_twin_tuple	tuple_rows[2];
	t_fl			array[2 * sizeof(t_twin_tuple) / sizeof(t_fl)];
}	t_mtx_2;

enum e_matrix_three_by_three_coordinates
{
	MATRIX_THREE_BY_THREE_ROW_0__COL_0,
	MATRIX_THREE_BY_THREE_ROW_0__COL_1,
	MATRIX_THREE_BY_THREE_ROW_0__COL_2,
	MATRIX_THREE_BY_THREE_ROW_1__COL_0,
	MATRIX_THREE_BY_THREE_ROW_1__COL_1,
	MATRIX_THREE_BY_THREE_ROW_1__COL_2,
	MATRIX_THREE_BY_THREE_ROW_2__COL_0,
	MATRIX_THREE_BY_THREE_ROW_2__COL_1,
	MATRIX_THREE_BY_THREE_ROW_2__COL_2
};

typedef struct s_triple_tuple {
	t_fl	col_0;
	t_fl	col_1;
	t_fl	col_2;
}	t_triple_tuple;

typedef union u_wrap_matrix_three_by_three
{
	t_triple_tuple	tuple_rows[3];
	t_fl			array[3 * sizeof(t_triple_tuple) / sizeof(t_fl)];
}	t_mtx_3;

enum e_matrix_four_by_four_coordinates
{
	MATRIX_FOUR_BY_FOUR_ROW_0__COL_0,
	MATRIX_FOUR_BY_FOUR_ROW_0__COL_1,
	MATRIX_FOUR_BY_FOUR_ROW_0__COL_2,
	MATRIX_FOUR_BY_FOUR_ROW_0__COL_3,
	MATRIX_FOUR_BY_FOUR_ROW_1__COL_0,
	MATRIX_FOUR_BY_FOUR_ROW_1__COL_1,
	MATRIX_FOUR_BY_FOUR_ROW_1__COL_2,
	MATRIX_FOUR_BY_FOUR_ROW_1__COL_3,
	MATRIX_FOUR_BY_FOUR_ROW_2__COL_0,
	MATRIX_FOUR_BY_FOUR_ROW_2__COL_1,
	MATRIX_FOUR_BY_FOUR_ROW_2__COL_2,
	MATRIX_FOUR_BY_FOUR_ROW_2__COL_3,
	MATRIX_FOUR_BY_FOUR_ROW_3__COL_0,
	MATRIX_FOUR_BY_FOUR_ROW_3__COL_1,
	MATRIX_FOUR_BY_FOUR_ROW_3__COL_2,
	MATRIX_FOUR_BY_FOUR_ROW_3__COL_3
};

typedef struct s_quad_tuple {
	t_fl	col_0;
	t_fl	col_1;
	t_fl	col_2;
	t_fl	col_3;
}	t_quad_tuple;

typedef union u_wrap_matrix_four_by_four
{
	t_quad_tuple	tuple_rows[4];
	t_fl			array[4 * sizeof(t_quad_tuple) / sizeof(t_fl)];
}	t_mtx_4;

typedef union u_wrap_matrices
{
	t_mtx_2		mtx_2;
	t_mtx_3		mtx_3;
	t_mtx_4		mtx_4;
}	t_matrices;

typedef union u_mtx_array
{
	t_matrices	matrices;
	t_fl		array[16];
}	t_mtx;

#endif
