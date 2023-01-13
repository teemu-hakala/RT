











#include "RT.h"

void	mouse_register_click_down(int button, t_point mouse_pointer, t_win *win)
{
	(void)button;
	win->input.mouse.prev = win->input.mouse.curr;
	win->input.mouse.curr = mouse_pointer;
	if (button == RIGHT_CLICK)
		win->input.mouse.rmb_is_down = true;
}

void	mouse_register_click_up(int button, t_point mouse_pointer, t_win *win)
{
	(void)button;
	(void)mouse_pointer;
	if (button == RIGHT_CLICK)
		win->input.mouse.rmb_is_down = false;
}

int	mouse_handler_down(int button, int x, int y, t_win *win)
{
	(void)button;
	(void)x;
	(void)y;
	(void)win;
	if (button == RIGHT_CLICK)
		mouse_register_click_down(button, (t_point){.row = y, .col = x}, win);
	else if (button == SCROLL_UP)
		apply_scroll_effect(win, 1);
	else if (button == SCROLL_DOWN)
		apply_scroll_effect(win, -1);
	return (EXIT_SUCCESS);
}

int	mouse_handler_move(int x, int y, t_win *win)
{
	(void)x;
	(void)y;
	(void)win;
	if (win->input.mouse.rmb_is_down == true)
	{
		win->input.mouse.diff = (t_point){.row = y - win->input.mouse.curr.row,
			.col = x - win->input.mouse.curr.col};
		navigate_camera(win);
		win->input.mouse.curr = (t_point){.row = y, .col = x};
	}
	return (EXIT_SUCCESS);
}

int	mouse_handler_up(int button, int x, int y, t_win *win)
{
	(void)button;
	(void)x;
	(void)y;
	(void)win;
	if (button == RIGHT_CLICK)
		mouse_register_click_up(button, (t_point){.row = y, .col = x}, win);
	return (EXIT_SUCCESS);
}
