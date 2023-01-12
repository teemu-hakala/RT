











#ifndef USER_INTERFACE_H
# define USER_INTERFACE_H
# include "objects.h"

typedef struct s_img	t_img;

typedef struct s_rectangle
{
	t_canvas	start;
	t_canvas	end;
	t_canvas	canvas;
}	t_rectangle;

enum e_progress_bar_flag
{
	BAR_NON_ACTION = 0b0,
	BAR_CLEAR = 0b1
};

void	put_rectangle_to_image(t_img img, t_rectangle image, \
	t_rectangle rect, t_tuple colour);
void	progress_bar(t_img img, t_fl progress_percentage, t_fl prev_perc);
void	toggle_key_user_interface(t_win *win);
t_img	progress_bar_image(t_win *win, t_canvas *bar_dimensions, uint8_t flag);
void	*progress_percentage(void *param);
void	clear_progress(t_progress progress[THREAD_COUNT], uint64_t frame);

#endif
