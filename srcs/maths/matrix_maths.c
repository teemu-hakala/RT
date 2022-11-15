/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_maths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:02:38 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/15 16:13:21 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RTv1.h"

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
			if (a[y][x] - b[y][x] < EPSILON)
				x++;
			else
				return (0);
		}
		y++;
	}
	return (1);
}

/* matrix multiplication for two identical square matrices */

void	matrix_multi_square(t_mtx *mtx, t_mtx *transformation, uint32_t size)
{
	t_mtx		temp;
	uint8_t		i;
	t_fl		res;
	t_coords	j;

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
				res += mtx->array[size * j.row + i] * \
				transformation->array[size * i + j.col];
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
	return (new);
}

/* swops rows and columns of the matrix */

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
