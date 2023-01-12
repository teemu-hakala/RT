











#ifndef USER_INTERFACE_H
# define USER_INTERFACE_H
# include "objects.h"
# define UP_STEP 0.0375
# define FORWARD_STEP 0.0375
# define LEFT_STEP 0.0375

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

enum e_key_code
{
	KEY_Q = 12,
	KEY_W = 13,
	KEY_E = 14,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_Z = 6,
	KEY_X = 7,
	KEY_C = 8
};

void	put_rectangle_to_image(t_img img, t_rectangle image, \
	t_rectangle rect, t_tuple colour);
void	progress_bar(t_img img, t_fl progress_percentage, t_fl prev_perc);
void	toggle_key_user_interface(t_win *win);
t_img	progress_bar_image(t_win *win, t_canvas *bar_dimensions, uint8_t flag);
void	*progress_percentage(void *param);
void	clear_progress(t_progress progress[THREAD_COUNT], uint64_t frame);
void	movement_agent(t_win *win, int key);
void	refresh_image(t_win *win);
void	apply_scroll_effect(t_win *win, int8_t direction);
void	camera_upwards(t_win *win, t_fl magnitude);
void	camera_forwards(t_win *win, t_fl magnitude);
void	camera_sideways(t_win *win, t_fl magnitude);
#endif
