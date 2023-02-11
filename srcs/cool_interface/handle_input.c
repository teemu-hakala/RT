











#include "RT.h"
#include <stdio.h>
void	esc_program(void)
{
	exit(EXIT_SUCCESS);
}

//should we add the press x to exit to this as well?

int	handle_on_key_down(int key, t_win *win)
{
	printf("key down: %i\n", key);
	if (key == ESC)
		esc_program();
	if (key == KEY_LEFT_SHIFT || key == KEY_Q || key == KEY_W || \
		key == KEY_E || key == KEY_A || key == KEY_S || key == KEY_D)
		multiple_keys_handler(key, win, true);
	if (key == KEY_LEFT_COMMAND || key == KEY_RIGHT_COMMAND)
		command_key_state(true);
	if (key == KEY_TABULATOR)
		toggle_key_user_interface(win);
	if (key == KEY_R || key == KEY_F)
		field_of_view_zoomer(win, key);
	if (key == KEY_P_ICTURE)
		save_screenshot_once_drawn(win);
	return (0);
}

int	handle_on_key_up(int key, t_win *win)
{
	printf("key up: %i\n", key);
	if (key == KEY_LEFT_SHIFT || key == KEY_Q || key == KEY_W || \
		key == KEY_E || key == KEY_A || key == KEY_S || key == KEY_D)
		multiple_keys_handler(key, win, false);
	return (0);
}
