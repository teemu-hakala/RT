
#ifndef PATTERNS_H
# define PATTERNS_H
# include "RT.h"

typedef enum e_pattern_type
{
	PATTERN_NONE = 0,
	PATTERN_VERTICAL_STRIPES = 1,
	PATTERN_HORIZONTAL_STRIPES = 2,
	PATTERN_CHECKERED = 3,
	PATTERN_CIRCLES = 4,
	PATTERN_GRADIENT = 5,
	PATTERN_ALIGN_CHECK = 6
}	t_type;

typedef enum e_cube_face
{
	FACE_FRONT = 0,
	FACE_BACK = 1,
	FACE_LEFT = 2,
	FACE_RIGHT = 3,
	FACE_UP = 4,
	FACE_DOWN = 5,
}	t_face;

// typedef struct s_uv_pattern
// {
// 	t_fl	width;
// 	t_fl	height;
// 	t_tuple	colour_a;
// 	t_tuple	colour_b;
// }				t_uv_pattern;

typedef struct s_uv_map
{
	t_fl	u;
	t_fl	v;
}			t_uv_map;

// typedef struct s_texture_map
// {
// 	t_uv_pattern pattern;
// 	t_uv_map	map;
// }				t_texture_map;



#endif