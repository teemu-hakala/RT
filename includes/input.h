











#ifndef INPUT_H
# define INPUT_H
# include "RT.h"

typedef struct s_win		t_win;

typedef enum e_scroll_mode
{
	MODE_NONE = 0,
	CAMERA_UP = 77,
	CAMERA_FORWARD,
	CAMERA_LEFT,
	CAMERA_FOV
}	t_scroll_mode;

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

typedef struct s_compounder
{
	uint64_t		compounds;
	t_scroll_mode	mode;
	int8_t			direction;
}	t_compounder;

typedef struct s_mouse
{
	t_point			prev;
	t_point			curr;
	t_point			diff;
	uint8_t			rmb_is_down : 1;
	t_scroll_mode	mode;
	t_compounder	compounder;
}	t_mouse;

typedef struct s_keyboards
{
	uint8_t	cmd_is_toggled : 1;
}	t_keyboard;

typedef struct s_user_inputs
{
	t_mouse		mouse;
	t_keyboard	keyboard;
}	t_input;

typedef union u_keys
{
	struct s_keys_that_are_down
	{
		uint32_t	w : 1;
		uint32_t	a : 1;
		uint32_t	s : 1;
		uint32_t	d : 1;
		uint32_t	q : 1;
		uint32_t	e : 1;
		uint32_t	r : 1;
		uint32_t	f : 1;
		uint32_t	left_shift : 1;
	}						keys_bitfield;
	uint32_t				keys_uint;
}	t_keys;

int		mouse_handler_down(int button, int x, int y, t_win *win);
int		mouse_handler_move(int x, int y, t_win *win);
int		mouse_handler_up(int button, int x, int y, t_win *win);
void	navigate_camera(t_win *win);
char	command_key_state(int change_state);

#endif
