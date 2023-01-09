











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
	uint64_t	frame;
}	t_renderer_info;

typedef enum e_frame_check
{
	FRAME_CHECK = 0b0,
	FRAME_NEXT = 0b1
}	t_frame_check;

int		put_image(t_win *win);
void	threaded_loop(t_win *win);

#endif
