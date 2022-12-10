











#ifndef MATRICES_H
# define MATRICES_H
# include "RT.h"

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
}	t_mtx;

#endif
