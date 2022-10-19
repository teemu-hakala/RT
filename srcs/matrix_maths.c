/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_maths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:21:03 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/19 11:56:52 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RTv1.h"

//use memallocarray to create matrix
//matrix needs to be freed once it's no longer in use

/* compares two matrices to see if they are the same. Returns 0 if different, 1
if equal */

int	matrix_comparison(t_fl **a, t_fl **b, uint32_t size)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (a[y][x] - b[y][x] < EPSILON) // "wrong - don't do this" https://floating-point-gui.de/errors/comparison/
				x++;
			else
				return (0);
		}
		y++;
	}
	return (1);
}

/* matrix multiplication for two identical 4 x 4 square matrices - eg. 4x4 * 4x4, or
3 x 3 * 3 x 3*/

void	matrix_multi_square(t_mtx *mtx, t_mtx *transformation, uint32_t size)
{
	t_mtx		temp;
	uint8_t		i;
	t_fl		res;
	t_index		j;

	j.row = 0;
	while (j.row < size)
	{
		j.col = 0;
		while (j.col < size)
		{
			res = 0;
			i = 0;
			while (i < size)
			{
				res += mtx->array[size * j.row + i] * transformation->array[size * i + j.col];
				i++;
			}
			temp.array[size * j.row + j.col] = res;
			j.col++;
		}
		j.row++;
	}
	*mtx = temp;
}

/* matrix multiplication for 4 x 4 matrix by a tuple */

t_tuple	matrix_tuple_multi(t_mtx *mtx, t_tuple *tuple)
{
	int		y;
	int		i;
	t_fl	res;
	t_tuple	new;

	y = 0;
	while (y < 4)
	{
		res = 0;
		i = 0;
		while (i < 4)
		{
			res = res + mtx->array[4 * y + i] * tuple->array[i];
			i++;
		}
		new.array[y] = res;
		y++;
	}
	// i = 0;
	// while (i < 4)
	// {
	// 	printf("%f, ", new.array[i]);
	// 	i++;
	// }
	return (new);
}

/* swops rows and columns of the matrix */

// t_fl	**transpose_matrix(t_fl **a)
// {
// 	t_fl	**temp;
// 	int		y;
// 	int		x;

// 	temp = (t_fl **)ft_memallocarray(sizeof(t_fl) * 4, sizeof(t_fl) * 4);
// 	if (temp)
// 	{
// 		y = 0;
// 		while (y < 4)
// 		{
// 			x = 0;
// 			while (x < 4)
// 			{
// 				temp[y][x] = a[x][y];
// 				x++;
// 			}
// 			y++;
// 		}
// 	}
// 	return (temp);
// }

t_mtx	transpose_matrix(t_mtx *mtx)
{
	t_mtx	temp;
	int		y;
	int		x;

	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			temp.array[4 * y + x] = mtx->array[4 * x + y];
			x++;
		}
		y++;
	}
	return (temp);
}

/*
t_mtx	*identity_matrix(t_mtx *dst)
{
	dst->tuple_rows[0] = (t_quad_tuple){1.0, 0.0, 0.0, 0.0};
	dst->tuple_rows[1] = (t_quad_tuple){0.0, 1.0, 0.0, 0.0};
	dst->tuple_rows[2] = (t_quad_tuple){0.0, 0.0, 1.0, 0.0};
	dst->tuple_rows[3] = (t_quad_tuple){0.0, 0.0, 0.0, 1.0};
	return (dst);
}*/

/*t_fl	**identity_matrix(void)
{
	t_fl	**id_matrix;

	id_matrix = (t_fl **)ft_memallocarray(sizeof(t_fl) * 4, sizeof(t_fl) * 4);
	if (id_matrix)
	{
		id_matrix[0][0] = 1.0;
		id_matrix[1][1] = 1.0;
		id_matrix[2][2] = 1.0;
		id_matrix[3][3] = 1.0;
	}
	return (id_matrix);
}*/

/* test function to print arrays*/

void	ft_print_num_array(t_fl **array, int y, int x)
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
			printf("%f, ", array[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
