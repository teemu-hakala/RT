/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:50:49 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/17 16:11:37 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RTv1.h"

/* the following functions are needed to invert a matrix.*/

/* function to remove a specified row and col from a matrix.
Returns a new matrix with 1 column and 1 row less*/

t_fl	**submatrix(t_fl **a, uint32_t size, uint32_t row, uint32_t col)
{
	t_fl		**new_matrix;
	uint32_t	new_matrix_row;
	uint32_t	new_matrix_col;
	uint32_t	row_a;
	uint32_t	col_a;

	new_matrix = (t_fl **)ft_memallocarray(
			sizeof(t_fl) * (size - 1),
			sizeof(t_fl) * (size - 1)
			);
	row_a = 0;
	new_matrix_row = 0;
	while (row_a <= size - 1)
	{
		if (row_a == row)
		{
			row_a++;
			continue ;
		}
		col_a = 0;
		new_matrix_col = 0;
		while (col_a <= size - 1)
		{
			if (col_a == col)
			{
				col_a++;
				continue ;
			}
			new_matrix[new_matrix_row][new_matrix_col] = a[row_a][col_a];
			col_a++;
			new_matrix_col++;
		}
		row_a++;
		new_matrix_row++;
	}
	return (new_matrix);
}

t_fl	matrix_minors(t_fl **a, uint32_t row, uint32_t col, uint32_t size)
{
	t_fl	**temp;
	t_fl	minor;

	temp = submatrix(a, size, row, col);
	minor = determinant(temp, size - 1);

	free (temp);
	return (minor);
}

t_fl	matrix_cofactor(t_fl **a, uint32_t row, uint32_t col, uint32_t size)
{
	t_fl	cofactor;
	t_fl	minor;

	minor = matrix_minors(a, row, col, size);
	if ((row + col)% 2 == 0)
		cofactor = minor;
	else
		cofactor = minor * -1;
	return (cofactor);
}

/* calculates the determinant of any sized matrix*/

t_fl	determinant(t_fl **a, uint32_t size)
{
	t_fl		det;
	uint32_t	col;

	col = 0;
	det = 0;
	if (size == 2)
		det = (a[0][0] * a[1][1]) - (a[0][1] * a[1][0]);
	else
	{
		while (col < size)
		{
			det = det + a[0][col] * matrix_cofactor(a, 0, col, size);
			col++;
		}
	}
	return (det);
}

/* matrix inversion - allows to reverse effects of matrix multiplication*/

t_fl	**matrix_inversion(t_fl **a, uint32_t size)
{
	t_fl		det;
	t_fl		**temp;
	uint32_t	y;
	uint32_t	x;

	det = determinant(a, size);
	if (det == 0)
		return (a);
	else
	{
		temp = (t_fl **)ft_memallocarray(sizeof(t_fl) * size, sizeof(t_fl) * size);
		if (temp)
		{
			y = (uint32_t)(-1);
			while (++y < size)
			{
				x = (uint32_t)(-1);
				while (++x < size)
					temp[y][x] = matrix_cofactor(a, y, x, size) / det;
			}
			a = transpose_matrix(temp);
		}
		ft_memdelarray((void **)temp, size);
	}
	return (a);
}
