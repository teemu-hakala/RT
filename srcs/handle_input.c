











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
	if (key == KEY_LEFT_COMMAND || key == KEY_RIGHT_COMMAND)
		command_key_state(true);
	if (key == KEY_TABULATOR)
		toggle_key_user_interface(win);
	return (0);
}
