











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
// void	print_time(t_world *world)
// {
// 	t_fl	time;
// 	t_fl	shape;
// 	time = world->hit.intersection.time;
// 	shape = world->hit.intersection.shape->type;
// 	printf("time: %f, shape: %f\n", time, shape);

// }
int	mouse_handler_down(int button, int x, int y, t_win *win)
{
	(void)button;
	(void)x;
	(void)y;
	(void)win;
	// t_ray	ray;

	if (button == RIGHT_CLICK)
		mouse_register_click_down(button, (t_point){.row = y, .col = x}, win);
	else if (button == SCROLL_UP)
		apply_scroll_effect(win, POSITIVE_DIRECTION);
	else if (button == SCROLL_DOWN)
		apply_scroll_effect(win, NEGATIVE_DIRECTION);
	// else if (button == LEFT_CLICK)
    // {
    //     ray = ray_for_pixel(&win->world.camera, (t_canvas){.horizontal = x, .vertical = y});
    //     colour_at(&win->world, ray);
	// 	printf("x: %i y: %i\n", x, y);
	// 	print_time(&win->world);
    // }
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
