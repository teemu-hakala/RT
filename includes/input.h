











#ifndef INPUT_H
# define INPUT_H
# include "RT.h"

typedef struct s_win	t_win;

enum e_event
{
	ON_KEY_DOWN = 2,
	ON_KEY_UP = 3,
	ON_MOUSE_DOWN = 4,
	ON_MOUSE_UP = 5,
	ON_MOUSE_MOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum e_mouse
{
	MOVE = 0,
	LEFT_CLICK = 1,
	RIGHT_CLICK = 2,
	MIDDLE_CLICK = 3,
	SCROLL_DOWN = 4,
	SCROLL_UP = 5
};

enum e_key
{
	KEY_LEFT_COMMAND = 259,
	KEY_RIGHT_COMMAND = 260,
	KEY_TABULATOR = 48
};

typedef struct s_point
{
	int		row;
	int		col;
}	t_point;

typedef struct s_mouse
{
	t_point	prev;
	t_point	curr;
	t_point	diff;
	uint8_t	rmb_is_down : 1;
}	t_mouse;

typedef struct s_keyboard
{
	uint8_t	cmd_is_toggled : 1;
}	t_keyboard;

typedef struct s_user_inputs
{
	t_mouse		mouse;
	t_keyboard	keyboard;
}	t_input;

int		mouse_handler_down(int button, int x, int y, t_win *win);
int		mouse_handler_move(int x, int y, t_win *win);
int		mouse_handler_up(int button, int x, int y, t_win *win);
void	navigate_camera(t_win *win);
char	command_key_state(int change_state);

#endif
