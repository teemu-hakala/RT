











#ifndef USER_INTERFACE_H
# define USER_INTERFACE_H
# include "objects.h"
# include <sys/stat.h>
# define UP_STEP 0.0375
# define FORWARD_STEP 0.0375
# define LEFT_STEP 0.0375
# define SCALE_COEFFICIENT 40.2
# define ZOOM_STEP 0.1
# define PPM_SUFFIX ".ppm"
# define PPM_BUFFER_SIZE 0b10000000000
# define PPM_MAGIC_NUMERAL "P6"
# define PPM_MAX_255 255

typedef struct s_img	t_img;

enum e_ppm_image_flag
{
	PPM_NON_ACTION = 0b0,
	PPM_NEW_IMAGE = 0b1,
	PPM_OUTPUT_IMAGE_DATA = 0b10
};

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

enum e_directions
{
	POSITIVE_DIRECTION = 1,
	KEY_R_DIRECTION = POSITIVE_DIRECTION,
	NEGATIVE_DIRECTION = -1,
	KEY_F_DIRECTION = NEGATIVE_DIRECTION
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
	KEY_C = 8,
	KEY_R = 15,
	KEY_F = 3,
	KEY_P_ICTURE = 35,
	KEY_LEFT_SHIFT = 257
};

void	put_rectangle_to_image(t_img img, t_rectangle image, \
	t_rectangle rect, t_tuple colour);
void	progress_bar(t_img img, t_fl progress_percentage, t_fl prev_perc);
void	toggle_key_user_interface(t_win *win);
t_img	progress_bar_image(t_win *win, t_canvas *bar_dimensions, uint8_t flag);
void	*progress_percentage(void *param);
void	clear_progress(t_progress progress[THREAD_COUNT], uint64_t frame);
int		movement_agent(void *win);
void	refresh_image(t_win *win);
void	apply_scroll_effect(t_win *win, int8_t direction);
void	camera_upwards(t_win *win, t_fl magnitude);
void	camera_forwards(t_win *win, t_fl magnitude);
void	camera_sideways(t_win *win, t_fl magnitude);
void	put_keys_image(t_win *win);
void	field_of_view_zoomer(t_win *win, int key);
void	compound_scroll_effect(t_win *win, int8_t direction);
void	field_of_view_delta(t_win *win, t_fl step);
void	save_screenshot_once_drawn(t_win *win);
int		get_new_file_for_image(void);
t_vec	*ppm_write_buffer(uint8_t flag, int fd);
void	ppm_push_string(char *string, uint64_t len);
void	buffer_ppm_image_header(t_win *win, int max_value);

#endif
