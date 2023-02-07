#include "RT.h"

void	multiple_keys_handler(int key, t_win *win, bool pressed)
{
	t_keys	keys;

	keys = win->input.keyboard.keys;
	keys.keys_bitfield.q = key == KEY_Q && pressed;
	keys.keys_bitfield.w = key == KEY_W && pressed;
	keys.keys_bitfield.e = key == KEY_E && pressed;
	keys.keys_bitfield.a = key == KEY_A && pressed;
	keys.keys_bitfield.s = key == KEY_S && pressed;
	keys.keys_bitfield.d = key == KEY_D && pressed;
	keys.keys_bitfield.left_shift = key == KEY_LEFT_SHIFT && pressed;
	mlx_loop_hook(win->mlx, put_image, win);
}
