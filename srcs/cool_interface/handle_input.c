/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:20:07 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/11 17:46:47 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	esc_program(void)
{
	exit(EXIT_SUCCESS);
}

int	handle_input(int key, t_win *win)
{
	if (key == ESC)
		esc_program();
	if (key == KEY_LEFT_COMMAND || key == KEY_RIGHT_COMMAND)
		command_key_state(true);
	if (key == KEY_TABULATOR)
		toggle_key_user_interface(win);
	if (key == KEY_Q || key == KEY_W || key == KEY_E \
		|| key == KEY_A || key == KEY_S || key == KEY_D)
		movement_agent(win, key);
	if (key == KEY_R || key == KEY_F)
		field_of_view_zoomer(win, key);
	if (key == KEY_P_ICTURE)
		save_screenshot_once_drawn(win);
	return (0);
}
