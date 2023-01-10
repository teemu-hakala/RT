











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


void	put_rectangle_to_image(t_img img, t_rectangle image,
	t_rectangle rect, t_tuple colour);
void	progress_bar(t_img img, t_fl progress_percentage);
void	toggle_key_user_interface(t_win *win);
t_img	progress_bar_image(t_win *win, t_canvas *bar_dimensions);

#endif
