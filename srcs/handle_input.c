#include "../includes/RTv1.h"

void	esc_program(void)
{
	exit(EXIT_SUCCESS);
}

int	handle_input(int key)
{
	// if (key == UP || key == DOWN || key == LEFT || key == RIGHT)
	// 	handle_translation(key, win);
	// if (key == ZOOM_IN || key == ZOOM_OUT)
	// 	handle_zoom(key, -1, -1, win);
	// if (key == COLOUR)
	// 	handle_colour(win);
	// if (key == ITER_UP || key == ITER_DOWN)
	// 	handle_iterations(key, win);
	// if (key == POWER)
	// 	handle_power(win);
	// if (key == RESET)
	// 	handle_reset(win);
	if (key == ESC)
		esc_program();
	return (0);
}
