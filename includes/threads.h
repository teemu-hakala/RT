











#ifndef THREADS_H
# define THREADS_H
# include "RT.h"
# include <pthread.h>
//# define THREAD_COUNT 512
//# define PIXEL_COUNT 256


typedef struct s_renderer_info
{
	t_win		*win;
	t_camera	*camera;
	t_canvas_64	from;
	uint64_t	pixels;
	pthread_t	thread_id;
}	t_renderer_info;

int		put_image(t_win *win);
void	threaded_loop(t_win *win);

#endif
