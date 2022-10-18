/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:13:53 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/18 16:14:46 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RTv1.h"

void	free_win(t_win *win)
{
	if (win->img.img)
		mlx_destroy_image(win->mlx, win->img.img);
	if (win->mlx && win->win)
		mlx_destroy_window(win->mlx, win->win);
}

void	handle_errors(t_win *win, char *str)
{
	free_win(win);
	ft_stderror(str);
	exit(EXIT_FAILURE);
}