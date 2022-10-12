/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:50:49 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/12 09:27:08 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RTv1.h"

/* the following functions are needed to invert a matrix.*/

/* function to remove a specified row and col from a matrix.
Returns a new matrix with 1 column and 1 row less*/

double	**submatrix(double **a, int size, int row, int col)
{
	double **new_matrix;
	int new_matrix_row;
	int new_matrix_col;
	int row_a;
	int col_a;

	new_matrix = (double **)ft_memallocarray(size - 1, size - 1);
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

double matrix_minors(double **a, int row, int col, int size)
{
	double **temp;
	double minor;

	temp = submatrix(a, size, row, col);
	minor = determinant(temp, size - 1);

	free (temp);
	return (minor);
}

double matrix_cofactor(double **a, int row, int col, int size)
{
	double cofactor;
	double minor;

	minor = matrix_minors(a, row, col, size);
	if ((row + col)% 2 == 0)
		cofactor = minor;
	else
		cofactor = minor * -1;
	return (cofactor);
}

/* calculates the determinant of any sized matrix*/

double determinant(double **a, int size)
{
	double	det;
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

double **matrix_inversion(double **a, int size)
{
	double det;
	double **temp;
	int y;
	int x;

	det = determinant(a, size);
	if (det == 0)
		return (a);
	else
	{
		temp = (double **)ft_memallocarray(size, size);
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
		ft_memdelarray(temp, size);
	}
	return (a);
}

int main(void)
{
	double **a4;
	a4 = (double **)ft_memallocarray(4, 4);

	a4[0][0] = -5;
	a4[0][1] = 2;
	a4[0][2] = 6;
	a4[0][3] = -8;

	a4[1][0] = 1;
	a4[1][1] = -5;
	a4[1][2] = 1;
	a4[1][3] = 8;

	a4[2][0] = 7;
	a4[2][1] = 7;
	a4[2][2] = -6;
	a4[2][3] = -7;

	a4[3][0] = 1;
	a4[3][1] = -3;
	a4[3][2] = 7;
	a4[3][3] = 4;

	printf("determinant a = %0.f\n", determinant(a4, 4));
	matrix_inversion(a4, 4);
	return (0);
}
