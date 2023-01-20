#include "RT.h"

void	act_upon_pressed_keys(t_win *win)
{
	/* no else ifs */
	if (win->input.keyboard.keys.keys_bitfield.w)
		/* look into movement_agent.c */
	if (win->input.keyboard.keys.keys_bitfield.a)
	/* think about refresh_image and act wisely,
		since multiple keys might be pressed during a frame
		maybe coordinate with mlx_loop_hooked function: */
}

// lisaa headeriin RT.h?
void	multiple_keys_handler(int key, t_win *win, bool pressed)
{
	/* signal to put_image to refresh_image after
		all keys have been handled */

	win->input.keyboard.multiple_key_was_pressed = true;
	/* handle t_keys combinations via struct aliases */
	if (key == KEY_W)
		win->input.keyboard.keys.keys_bitfield.w = pressed;
	else if () /* use else ifs */
		;
	act_upon_pressed_keys();
}
