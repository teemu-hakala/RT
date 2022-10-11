/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:02:35 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/11 11:04:11 by deelliot         ###   ########.fr       */
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

int main(void)
{
	double **a;
	double **c;

	a = (double **)ft_memallocarray(4, 4);

	a[0][0] = -6;
	a[0][1] = 1;
	a[0][2] = 1;
	a[0][3] = 6;

	a[1][0] = -8;
	a[1][1] = 5;
	a[1][2] =8;
	a[1][3] = 6;

	a[2][0] = -1;
	a[2][1] = 0;
	a[2][2] = 8;
	a[2][3] = 2;

	a[3][0] = -7;
	a[3][1] = 1;
	a[3][2] = -1;
	a[3][3] = 1;

	ft_print_num_array(a, 4, 4);
	printf("\n\n");
	c = submatrix(a, 4, 2, 1);
	ft_print_num_array(c, 3, 3);
	return (0);
}