











#include "RT.h"
#include <stdio.h>
void	esc_program(void)
{
	exit(EXIT_SUCCESS);
}

//should we add the press x to exit to this as well?

int	handle_input(int key, t_win *win)
{
	printf("key %i\n", key);
	if (key == ESC)
		esc_program();
	else if (key == KEY_LEFT_COMMAND || key == KEY_RIGHT_COMMAND)
		command_key_state(true);
	else if (key == KEY_TABULATOR)
		toggle_key_user_interface(win);
	else if (key == KEY_Q || key == KEY_W || key == KEY_E \
		|| key == KEY_A || key == KEY_S || key == KEY_D)
		movement_agent(win, key);
	else if (key == KEY_R || key == KEY_F)
		field_of_view_zoomer(win, key);
	else if (key == KEY_P_ICTURE)
		save_screenshot_once_drawn(win);
	else if (key == KEY_DOT)
		loop_filters(win);
	return (0);
}
