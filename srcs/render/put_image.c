










#include "RT.h"
#include <stdio.h>

void	init_progress_mutex(t_progress progress[THREAD_COUNT])
{
	uint16_t	t;

	t = 0;
	while (t < THREAD_COUNT)
	{
		pthread_mutex_init(&progress[t].mutex, NULL);
		t++;
	}
}

void	clear_progress(t_progress progress[THREAD_COUNT], uint64_t frame)
{
	uint16_t	t;

	t = THREAD_COUNT;
	while (t-- > 0)
	{
		pthread_mutex_lock(&progress[t].mutex);
		progress[t].pixels = 0;
		progress[t].frame = frame;
		pthread_mutex_unlock(&progress[t].mutex);
	}
}

void	progress_percentage_loop(uint64_t *pixel_progress, t_win *win)
{
	uint16_t	t;

	*pixel_progress = 0;
	t = 0;
	while (t < THREAD_COUNT)
	{
		pthread_testcancel();
		*pixel_progress += win->progress[t].pixels;
		t++;
	}
}

void	*progress_percentage(void *param)
{
	t_win					*win;
	uint64_t				pixel_progress;
	t_fl					percentage;
	t_fl					previous_percentage;
	t_canvas				c;

	win = (t_win *)param;
	c = win->world.camera.canvas;
	pixel_progress = 0;
	previous_percentage = 0;
	while (pixel_progress < c.horizontal * c.vertical)
	{
		progress_percentage_loop(&pixel_progress, win);
		percentage = ((t_fl)pixel_progress) / (c.horizontal * c.vertical);
		progress_bar(progress_bar_image(win, \
			&(t_canvas){.horizontal = c.horizontal - 20, .vertical = 20}, \
			BAR_NON_ACTION), percentage, previous_percentage);
		previous_percentage = percentage;
	}
	pthread_mutex_lock(&win->drawn_mutex);
	win->drawn = true;
	pthread_mutex_unlock(&win->drawn_mutex);
	return (NULL);
}

int	put_image(t_win *win)
{
	static t_progress	progress[THREAD_COUNT];
	static int			first = 1;

	if (first)
	{
		win->progress = progress;
		init_progress_mutex(progress);
		progress_bar_image(win, \
			&(t_canvas){.horizontal = WIDTH - 20, .vertical = 20}, BAR_CLEAR);
		threaded_loop(win, progress);
		first = 0;
		pthread_create(&win->bar_thread, NULL, progress_percentage, win);
		win->drawn = 0;
	}
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
	put_keys_image(win);
	if (win->drawn == false)
		mlx_put_image_to_window(win->mlx, win->win, \
			progress_bar_image(win, NULL, BAR_NON_ACTION).img, 10, \
				win->world.camera.canvas.vertical - 30);
	if (win->drawn == true)
		mlx_loop_hook(win->mlx, NULL, NULL);
	return (0);
}
