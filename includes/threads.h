











#ifndef THREADS_H
# define THREADS_H
# include "RT.h"
# include <pthread.h>
# define THREAD_COUNT 24

typedef struct s_progress
{
	uint64_t		pixels;
	uint64_t		frame;
	pthread_mutex_t	mutex;
}	t_progress;

typedef struct s_renderer_info
{
	t_win		*win;
	t_camera	*camera;
	t_canvas_64	from;
	uint64_t	pixels;
	pthread_t	thread_id;
	uint64_t	frame;
	uint64_t	*current_frame;
	t_progress	*progress;
	uint8_t		is_last;
}	t_renderer_info;

typedef enum e_frame_check
{
	FRAME_CHECK = 0b0,
	FRAME_NEXT = 0b1
}	t_frame_check;

typedef struct s_norme_render
{
	t_renderer_info	*info;
	t_canvas		canvas;
	t_world			*world_safe;
}	t_norme_render;

int		put_image(t_win *win);
void	threaded_loop(t_win *win, t_progress progress[THREAD_COUNT]);
void	*world_end(t_world *ending_world, pthread_mutex_t *progress_mutex);
t_world	world_selectively_shallow_copy(t_world *original);
void	threaded_loop_mid(t_win *win);

#endif
