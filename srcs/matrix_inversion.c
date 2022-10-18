/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:50:49 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/18 12:42:23 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RTv1.h"

/* the following functions are needed to invert a matrix.*/

/* function to remove a specified row and col from a matrix.
Returns a new matrix with 1 column and 1 row less*/

t_mtx submatrix(t_mtx *mtx, uint32_t size, uint32_t row, uint32_t col)
{
	t_mtx		new_matrix;
	uint32_t	row_new;
	uint32_t	col_new;
	uint32_t	row_old;
	uint32_t	col_old;

	row_old = 0;
	row_new = 0;
	while (row_old <= size - 1)
	{
		if (row_old == row)
		{
			row_old++;
			continue ;
		}
		col_old = 0;
		col_new = 0;
		while (col_old <= size - 1)
		{
			if (col_old == col)
			{
				col_old++;
				continue ;
			}
			new_matrix.array[(size - 1) * row_new + col_new] = mtx->array[size * row_old + col_old];
			col_old++;
			col_new++;
		}
		row_old++;
		row_new++;
	}
	return (new_matrix);
}

t_fl	matrix_minors(t_mtx *mtx, uint32_t row, uint32_t col, uint32_t size)
{
	t_mtx	temp;
	t_fl	minor;

	temp = submatrix(mtx, size, row, col);
	minor = determinant(&temp, size - 1);

	return (minor);
}

t_fl	matrix_cofactor(t_mtx *mtx, uint32_t row, uint32_t col, uint32_t size)
{
	t_fl	cofactor;
	t_fl	minor;

	minor = matrix_minors(mtx, row, col, size);
	if ((row + col) % 2 == 0)
		cofactor = minor;
	else
		cofactor = minor * -1;
	return (cofactor);
}

/* calculates the determinant of any sized matrix*/

t_fl	determinant(t_mtx *mtx, uint32_t size)
{
	t_fl		det;
	uint32_t	col;

	col = 0;
	det = 0;
	if (size == 2)
		det = (mtx->array[0] * mtx->array[2 * 1 + 1]) - (mtx->array[2 * 0 + 1] * mtx->array[2 * 1 + 0]);
	else
	{
		while (col < size)
		{
			det = det + mtx->array[size * 0 + col] * matrix_cofactor(mtx, 0, col, size);
			col++;
		}
	}
	return (det);
}

/* matrix inversion - allows to reverse effects of matrix multiplication*/

void	matrix_inversion(t_mtx_4 *mtx, uint32_t size)
{
	t_fl		det;
	t_mtx_4		temp;
	uint32_t	y;
	uint32_t	x;

	det = determinant((t_mtx *)mtx, size);
	if (det == 0)
	{
		printf("det = %f\n", det);
		return ;
	}

	else
	{
		//temp = (t_fl **)ft_memallocarray(sizeof(t_fl) * size, sizeof(t_fl) * size);
		//if (temp)
		//{
		y = (uint32_t)(-1);
		while (++y < size)
		{
			x = (uint32_t)(-1);
			while (++x < size)
				temp.array[size * y + x] = matrix_cofactor((t_mtx *)mtx, y, x, size) / det;
		}
		*mtx = transpose_matrix(&temp);
		//}
		//ft_memdelarray((void **)temp, size);
	}
}
