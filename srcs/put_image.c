










#include <stdio.h>
#include "RT.h"

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

t_fl	progress_percentage(t_progress progress[THREAD_COUNT])
{
	uint64_t	pixel_progress;
	uint16_t	t;

	pixel_progress = 0;
	t = 0;
	while (t < THREAD_COUNT)
	{
		pixel_progress += progress[t].pixels;
		t++;
	}
	return (((t_fl)pixel_progress) / (WIDTH * HEIGHT));
}

int	put_image(t_win *win)
{
	static t_progress	progress[THREAD_COUNT];
	static int			first = 1;

	if (first)
	{
		win->progress = progress;
		init_progress_mutex(progress);
		// threaded_loop_mid(win);
		threaded_loop(win, progress);
		first = 0;
	}
	progress_bar(progress_bar_image(win, &(t_canvas){.horizontal = WIDTH - 20, \
		.vertical = 20}), progress_percentage(progress));
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
	mlx_put_image_to_window(win->mlx, win->win, \
		progress_bar_image(win, NULL).img, 10, HEIGHT - 30);
	return (0);
}
