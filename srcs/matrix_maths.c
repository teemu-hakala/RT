/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_maths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:21:03 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/10 09:19:39 by deelliot         ###   ########.fr       */
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

double **matrix_multi_square(double **a, double **b, int size)
{
	double **temp;
	int x; //col
	int y; //row
	int i;
	double res;

	temp = (double **)ft_memallocarray(size, size);
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

int main(void)
{
	double **a;
	double **b;
	double **c;
	int x;

	a = (double **)ft_memallocarray(3, 3);
	a[0][0] = 0;
	a[0][1] = 1;
	a[0][2] = 2;
	a[1][0] = 3;
	a[1][1] = 4;
	a[1][2] = 5;
	a[2][0] = 6;
	a[2][1] = 7;
	a[2][2] = 8;

	b = (double **)ft_memallocarray(3, 3);
	b[0][0] = 9;
	b[0][1] = 10;
	b[0][2] = 11;
	b[1][0] = 12;
	b[1][1] = 13;
	b[1][2] = 14;
	b[2][0] = 15;
	b[2][1] = 16;
	b[2][2] = 17;
	x = matrix_comparison(a, b, 3);
	if (x == 1)
		printf("a = b\n");
	else
		printf("a != b\n");
	c = matrix_multi_square(a, b, 3);
	ft_print_num_array(c, 3, 3);
	return (0);
}
