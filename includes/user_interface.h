











#ifndef USER_INTERFACE_H
# define USER_INTERFACE_H
# include "objects.h"

typedef struct s_img	t_img;

typedef struct s_rectangle
{
	t_canvas	start;
	t_canvas	end;
}	t_rectangle;

void	progress_bar(t_img img, t_fl progress_percentage);

#endif
