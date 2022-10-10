/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_maths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:21:03 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/10 08:39:42 by deelliot         ###   ########.fr       */
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

double **matrix_multi_4x4(double **a, double **b)
{
	double **temp;
	int x;
	int y;
	int i;
	double res;

	temp = (double **)ft_memallocarray(3, 3);
	y = 0;
	while (y < 3)
	{
		x = 0;
		while (x < 3)
		{
			res = 0;
			i = 0;
			while (i < 3)
			{
				res = res + a[y][x + i] * b[x + i][y];
				i++;
			}
			temp[y][x] = res;
			x++;
		}
		y++;
	}
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
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

// int main(void)
// {
// 	double **a;
// 	double **b;
// 	double **c;
// 	int x;

// 	a = (double **)ft_memallocarray(3, 3);
// 	a[0][0] = 0;
// 	a[0][1] = 2;
// 	a[0][2] = 3;
// 	a[1][0] = 5;
// 	a[1][1] = 7;
// 	a[1][2] = 3;
// 	a[2][0] = 4;
// 	a[2][1] = 5;
// 	a[2][2] = 3;

// 	b = (double **)ft_memallocarray(3, 3);
// 	b[0][0] = 0;
// 	b[0][1] = 2;
// 	b[0][2] = 3;
// 	b[1][0] = 5;
// 	b[1][1] = 6;
// 	b[1][2] = 3;
// 	b[2][0] = 5;
// 	b[2][1] = 5;
// 	b[2][2] = 3;
// 	x = matrix_comparison(a, b, 3);
// 	if (x == 1)
// 		printf("a = b\n");
// 	else
// 		printf("a != b\n");

// 	return (0);
// }
