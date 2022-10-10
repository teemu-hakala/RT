/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_maths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:21:03 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/10 16:32:56 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RTv1.h"

//use memallocarray to create matrix
//matrix needs to be freed once it's no longer in use

int	matrix_comparison(double **a, double **b, int size)
{
	int x;
	int y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (a[y][x] - b[y][x] < EPSILON)
				x++;
			else
				return (0);
		}
		y++;
	}
	return (1);
}

/* matrix multiplication for two identical square matrices - eg. 4x4 * 4x4, or
3 x 3 * 3 x 3*/

double	**matrix_multi_square(double **a, double **b, int size)
{
	double **temp;
	int x; //col
	int y; //row
	int i;
	double res;

	temp = (double **)ft_memallocarray(size, size);
	if (temp)
	{
		y = 0;
		while (y < size)
		{
			x = 0;
			while (x < size)
			{
				res = 0;
				i = 0;
				while (i < size)
				{
					res = res + a[y][i] * b[i][x];
					i++;
				}
				temp[y][x] = res;
				x++;
			}
			y++;
		}
		}
	return (temp);
}

double	*matrix_tuple_multi(double **a, t_tuple tuple)
{
	double **b;
	int y; //row
	int i;
	double res;
	double *temp;

	b = tuple_to_array(tuple);
	ft_print_num_array(b, 4, 1);
	temp = ft_memalloc(4);
	if (temp)
	{
		y = 0;
		while (y < 4)
		{
			res = 0;
			i = 0;
			while (i < 4)
			{
				res = res + a[y][i] * b[i][0];
				i++;
			}
			temp[y] = res;
			y++;
		}
	}
	ft_memdelarray((void *)b, 4);
	return (temp);
}

double	**transpose_matrix(double **a)
{
	double **temp;
	int y;
	int x;

	temp = (double **)ft_memallocarray(4, 4);
	if (temp)
	{
		y = 0;
		while (y < 4)
		{
			x = 0;
			while (x < 4)
			{
				temp[y][x] = a[x][y];
				x++;
			}
			y++;
		}
	}
	return (temp);
}

double	matrix_determinant(double **a)
{
	double temp;

	temp = (a[0][0] * a[1][1]) - (a[0][1] * a[1][0]);
	return (temp);
}

void	ft_print_num_array(double **array, int y, int x)
{
	int	i;
	int	j;

	if (!array)
		return ;
	if (y == 0 || x == 0)
		return ;
	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			ft_putnbr(array[i][j]);
			write(1, ",", 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

double **identity_matrix(void)
{
	double **id_matrix;

	id_matrix = (double **)ft_memallocarray(4, 4);
	if (id_matrix)
	{
		id_matrix[0][0] = 1;
		id_matrix[1][1] = 1;
		id_matrix[2][2] = 1;
		id_matrix[3][3] = 1;
	}
	return (id_matrix);
}

double **submatrix(double **a, int size, int row, int col)
{
	double **new_matrix;

	new_matrix = (double **)ft_memallocarray(size - 1, size - 1);
	


}