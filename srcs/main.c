/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:02:35 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/10 08:40:27 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RTv1.h"

int main(void)
{
	t_win	win;

	initialise_window(&win);
	mlx_hook(win.win, KEY_DOWN, 0, handle_input, &win);
	mlx_loop(win.mlx);
	return (0);
}
