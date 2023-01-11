










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

void	clear_progress(t_progress progress[THREAD_COUNT], uint64_t frame)
{
	uint16_t	t;

	t = THREAD_COUNT;
	printf("clear_progress: frame %llu\n", frame);
	while (t-- > 0)
	{
		pthread_mutex_lock(&progress[t].mutex);
		progress[t].pixels = 0;
		progress[t].frame = frame;
		pthread_mutex_unlock(&progress[t].mutex);
	}
}

void	cleanup(void *param)
{
	t_win	*win;

	win = (t_win *)param;
	printf("cleanup function called\n");
}

void	*progress_percentage(void *param)
{
	static const uint64_t	pixels = WIDTH * HEIGHT;
	t_win					*win;
	uint64_t				pixel_progress;
	uint16_t				t;
	t_fl					percentage;
	t_fl					previous_percentage;
	uint64_t				frame_previous;
	long	asd;

	win = (t_win *)param;
	pthread_cleanup_push(&cleanup, win);
	pixel_progress = 0;
	asd = (long)win->bar_thread;
	printf("%li : spawned progress_percentage thread\n", asd);
	frame_previous = win->progress[0].frame;
	previous_percentage = 0;
	while (pixel_progress < pixels)
	{
		pixel_progress = 0;
		t = 0;
		while (t < THREAD_COUNT)
		{
			pixel_progress += win->progress[t].pixels;
			if (win->progress[t].frame != frame_previous)
			{
				printf("testcancel before😇\n");
				pthread_testcancel();
				printf("testcancel after🤜\n");
				printf("frame doesn't match\n");
				//pthread_detach(pthread_self());
				pixel_progress = 0;
				frame_previous = win->progress[t].frame;
				t = 0;
				previous_percentage = 0;
				progress_bar_image(win, \
					&(t_canvas){.horizontal = WIDTH - 20, .vertical = 20}, BAR_CLEAR);
				while (frame_previous != win->progress[t].frame)
					printf("%llu != %llu RAAAAHH\n", frame_previous, win->progress[t].frame);
				continue ;
			}
			frame_previous = win->progress[t].frame;
			t++;
		}
		percentage = ((t_fl)pixel_progress) / pixels;
		//printf("percentage %lf%%\n", percentage);
		progress_bar(progress_bar_image(win, \
			&(t_canvas){.horizontal = WIDTH - 20, .vertical = 20}, \
			BAR_NON_ACTION), percentage, previous_percentage);
		previous_percentage = percentage;
	}
	pthread_mutex_lock(&win->drawn_mutex);
	win->drawn = true;
	// printf("%li : win->drawn true\n", asd);
	pthread_mutex_unlock(&win->drawn_mutex);
	pthread_cleanup_pop(1);
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
		// threaded_loop_mid(win);
		threaded_loop(win, progress);
		first = 0;
		progress_bar_image(win, \
			&(t_canvas){.horizontal = WIDTH - 20, .vertical = 20}, BAR_CLEAR);
		pthread_create(&win->bar_thread, NULL, progress_percentage, win);
		win->drawn = 0;
	}
	mlx_clear_window(win->mlx, win->win);
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
	// printf("win->drawn %hhi\n", win->drawn);
	if (win->drawn == false)
	{
		mlx_put_image_to_window(win->mlx, win->win, \
			progress_bar_image(win, NULL, BAR_NON_ACTION).img, 10, HEIGHT - 30);
		// printf("image_put_to_window\n");
	}
	return (0);
}
