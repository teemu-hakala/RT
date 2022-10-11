/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:02:35 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/11 11:21:17 by deelliot         ###   ########.fr       */
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
	double **a4;
	double **a3;
	double minor;

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

	a3 = (double **)ft_memallocarray(3, 3);

	a3[0][0] = 3;
	a3[0][1] = 5;
	a3[0][2] = 0;

	a3[1][0] = 2;
	a3[1][1] = -1;
	a3[1][2] =-7;

	a3[2][0] = 6;
	a3[2][1] = -1;
	a3[2][2] = 5;

	minor = matrix_minors(a3, 1, 0);
	printf("%f\n", minor);
	return (0);
}