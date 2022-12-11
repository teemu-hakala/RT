











#ifndef OBJECTS_H
# define OBJECTS_H
# include "RT.h"
# include "patterns.h"

typedef enum e_object_type
{
	OBJECT_INDEX_OFFSET = 42,
	OBJECT_PLANE = 42,
	OBJECT_SPHERE = 43,
	OBJECT_CONE = 44,
	OBJECT_CYLINDER = 45,
}	t_object_type;

typedef struct s_phong_colour_constituents
{
	t_tuple		amb;
	t_tuple		diff;
	t_tuple		spec;
}				t_const;

typedef struct s_transform
{
	t_mtx	matrix;
	t_mtx	inverse;
	t_tuple	translation;
	t_tuple	rotation;
	t_tuple	scale;
}	t_transform;

typedef struct s_pattern
{
	enum e_pattern_type	type;
	t_tuple				colour_a;
	t_tuple				colour_b;
	t_transform			transform;
}	t_pattern;

typedef struct s_material
{
	t_fl		ambient;
	t_fl		diffuse;
	t_fl		specular;
	t_fl		shininess;
	t_tuple		init_colour;
	t_tuple		final_colour;
	t_tuple		col_mash;
}				t_material;

typedef struct s_comp
{
	t_fl			time;
	t_object_type	type;
	t_tuple			point;
	t_tuple			over_point;
	t_phong			vectors;
	int				inside;
}				t_comp;

typedef struct s_info
{
	t_material	material;
	t_const		channels;
}				t_info;

typedef struct s_plane
{
	t_tuple		origin;
	t_transform	transform;
	t_material	material;
	t_pattern	pattern;
}	t_plane;

typedef struct s_sphere
{
	t_tuple		origin;
	t_transform	transform;
	t_material	material;
	t_pattern	pattern;
}	t_sphere;

typedef struct s_cone
{
	t_tuple		origin;
	t_transform	transform;
	t_material	material;
	t_pattern	pattern;
	t_fl		radius;
	t_fl		min;
	t_fl		max;
	int			closed;
}	t_cone;

typedef struct s_cylinder
{
	t_tuple		origin;
	t_transform	transform;
	t_material	material;
	t_pattern	pattern;
	t_fl		radius;
	t_fl		min;
	t_fl		max;
	int			closed;
}	t_cylinder;

typedef struct s_light
{
	t_tuple		position;
	t_tuple		intensity;
}	t_light;

typedef struct s_canvas_size
{
	uint16_t	vertical;
	uint16_t	horizontal;
}	t_canvas;

typedef struct s_camera
{
	t_tuple		origin;
	t_transform	transform;
	t_tuple		center_of_interest;
	t_canvas	canvas;
	t_fl		field_of_view;
	t_fl		pixel_size;
	t_fl		half_width;
	t_fl		half_height;
}	t_camera;

union	u_object
{
	t_plane		plane;
	t_sphere	sphere;
	t_cone		cone;
	t_cylinder	cylinder;
};

typedef struct s_object
{
	union u_object		object;
	enum e_object_type	type;
}	t_object;

typedef t_tuple	(*t_normal_fn)(void *, t_tuple *);

typedef void	(*t_object_transform)(t_object *);

#endif
