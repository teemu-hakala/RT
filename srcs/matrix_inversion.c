/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:50:49 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/12 15:03:43 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RTv1.h"

/* the following functions are needed to invert a matrix.*/

/* function to remove a specified row and col from a matrix.
Returns a new matrix with 1 column and 1 row less*/

t_fl	**submatrix(t_fl **a, int size, int row, int col)
{
	t_fl **new_matrix;
	int new_matrix_row;
	int new_matrix_col;
	int row_a;
	int col_a;

	new_matrix = (t_fl **)ft_memallocarray(sizeof(t_fl) * size - 1, sizeof(t_fl) * size - 1);
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

t_fl matrix_minors(t_fl **a, int row, int col, int size)
{
	t_fl **temp;
	t_fl minor;

	temp = submatrix(a, size, row, col);
	minor = determinant(temp, size - 1);

	free (temp);
	return (minor);
}

t_fl matrix_cofactor(t_fl **a, int row, int col, int size)
{
	t_fl cofactor;
	t_fl minor;

	minor = matrix_minors(a, row, col, size);
	if ((row + col)% 2 == 0)
		cofactor = minor;
	else
		cofactor = minor * -1;
	return (cofactor);
}

/* calculates the determinant of any sized matrix*/

t_fl determinant(t_fl **a, int size)
{
	t_fl	det;
	int	col;

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

t_fl **matrix_inversion(t_fl **a, int size)
{
	t_fl det;
	t_fl **temp;
	int y;
	int x;

	det = determinant(a, size);
	if (det == 0)
		return (a);
	else
	{
		temp = (t_fl **)ft_memallocarray(sizeof(t_fl) * size, sizeof(t_fl) * size);
		if (temp)
		{
			y = -1;
			while (++y < size)
			{
				x = -1;
				while (++x < size)
					temp[y][x] = matrix_cofactor(a, y, x, size) / det;
			}
			a = transpose_matrix(temp);
		}
		ft_memdelarray((void **)temp, size);
	}
	return (a);
}
