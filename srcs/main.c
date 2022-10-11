/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:02:35 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/11 17:04:31 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RTv1.h"

// int main(void)
// {
// 	t_win	win;

// 	initialise_window(&win);
// 	mlx_hook(win.win, KEY_DOWN, 0, handle_input, &win);
// 	mlx_loop(win.mlx);
// 	return (0);
// }

void	test_three_matrix_a3(void)
{
	double **a3;

	a3 = (double **)ft_memallocarray(3, 3);

	a3[0][0] = 1;
	a3[0][1] = 2;
	a3[0][2] = 6;

	a3[1][0] = -5;
	a3[1][1] = 8;
	a3[1][2] =-4;

	a3[2][0] = 2;
	a3[2][1] = 6;
	a3[2][2] = 4;

	double minor;
	double cofactor;
	double determinant;

	cofactor = matrix_cofactor(a3, 0, 0);
	printf("cofactor = %f\n", cofactor);
	cofactor = matrix_cofactor(a3, 0, 1);
	printf("cofactor = %f\n", cofactor);
	cofactor = matrix_cofactor(a3, 0, 2);
	printf("cofactor = %f\n", cofactor);
	minor = matrix_minors(a3, 0, 0);
	printf("minor: %f\n", minor);
}

void	test_matrix_tuple_multi_four_matrix(void)
{
	double **a4;

	a4 = (double **)ft_memallocarray(4, 4);

	a4[0][0] = -6;
	a4[0][1] = 1;
	a4[0][2] = 1;
	a4[0][3] = 6;

	a4[1][0] = -8;
	a4[1][1] = 5;
	a4[1][2] =8;
	a4[1][3] = 6;

	a4[2][0] = -1;
	a4[2][1] = 0;
	a4[2][2] = 8;
	a4[2][3] = 2;

	a4[3][0] = -7;
	a4[3][1] = 1;
	a4[3][2] = -1;
	a4[3][3] = 1;
}

void	test_matrix_determinant(void)
{

}

void	test_tuple_reading(void)
{
	t_tuple tuple;

	tuple.tuple = (t_units){ 1, 3, 5, 0 };

	int i;
	i = 0;
	while (i < 4)
	{
		printf("%0.f, ", tuple.array[i]);
		i++;
	}
}

int main(void)
{
	// int count;
	// printf("no. cols = %d\n", count);

	return (0);
}