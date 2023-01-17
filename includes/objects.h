











#ifndef OBJECTS_H
# define OBJECTS_H
# include "RT.h"
# include "patterns.h"

typedef enum e_light_type
{
	LIGHT_NOT_FOUND = 0,
	LIGHT_SPOT = 52,
	LIGHT_PARALLEL = 53
}	t_light_type;

typedef enum e_object_type
{
	OBJECT_PLANE = 0,
	OBJECT_SPHERE = 1,
	OBJECT_CONE = 2,
	OBJECT_CYLINDER = 3,
	OBJECT_CUBE = 4,
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

typedef struct s_ppm_image
{
	int		fd;
	char	*name;
	int		height;
	int		width;
	int		max_value;
	t_tuple	**pixels;
}				t_ppm_image;

typedef struct s_texture
{
	enum e_text_type	type;
	t_fl				width;
	t_fl				height;
	t_tuple				colour_a;
	t_tuple				colour_b;
	int					face;
	t_tuple				main[6];
	t_tuple				ul[6];
	t_tuple				ur[6];
	t_tuple				br[6];
	t_tuple				bl[6];
	t_uv_map			map;
	t_transform			transform; //maybe
	t_ppm_image			image[6];
}				t_texture;

typedef struct s_pattern
{
	enum e_pattern_type	type;
	t_fl				width;
	t_fl				height;
	t_tuple				colour_a;
	t_tuple				colour_b;
	t_transform			transform;
}	t_pattern;

typedef struct s_appearance
{
	t_pattern	pattern;
	t_texture	texture;
}				t_appearance;

typedef struct s_material
{
	t_fl		ambient;
	t_fl		diffuse;
	t_fl		specular;
	t_fl		shininess;
	t_tuple		init_colour;
	t_tuple		final_colour;
	t_tuple		col_mash;
	t_fl		reflectiveness;
}				t_material;

typedef struct s_comp
{
	t_fl			time;
	t_object_type	type;
	t_tuple			point;
	t_tuple			over_point;
	t_phong			vectors;
	int				inside;
	t_tuple			reflectv;
}				t_comp;

typedef struct s_info
{
	t_material		material;
	t_appearance	appearance;
	t_transform		transform;
	t_const			channels;
	t_tuple			col;
}				t_info;

typedef struct s_plane
{
	t_tuple			origin;
	t_transform		transform;
	t_material		material;
	t_appearance	appearance;
}	t_plane;

typedef struct s_sphere
{
	t_tuple			origin;
	t_transform		transform;
	t_material		material;
	t_appearance	appearance;
}	t_sphere;

typedef struct s_cone
{
	t_tuple			origin;
	t_transform		transform;
	t_material		material;
	t_appearance	appearance;
	t_fl			radius;
	t_fl			min;
	t_fl			max;
	int				closed;
}	t_cone;

typedef struct s_cylinder
{
	t_tuple			origin;
	t_transform		transform;
	t_material		material;
	t_appearance	appearance;
	t_fl			radius;
	t_fl			min;
	t_fl			max;
	int				closed;
}	t_cylinder;

typedef struct s_cube
{
	t_tuple			origin;
	t_transform		transform;
	t_material		material;
	t_appearance	appearance;
	t_fl			length;
}	t_cube;

typedef struct s_light
{
	t_tuple			position;
	t_tuple			intensity;
	t_tuple			direction;
	t_light_type	type;
}	t_light;

typedef struct s_canvas_size
{
	uint16_t	vertical;
	uint16_t	horizontal;
}	t_canvas;

typedef struct s_canvas_size_64
{
	uint64_t	vertical;
	uint64_t	horizontal;
}	t_canvas_64;

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
	t_cube		cube;
};

typedef struct s_object
{
	union u_object		object;
	enum e_object_type	type;
	uint64_t			parent;
}	t_object;

typedef struct s_group
{
	t_vec		objects;
	t_transform	transform;
	//t_material	material;
}				t_group;


typedef t_tuple	(*t_normal_fn)(void *, t_tuple *);

typedef void	(*t_object_transform)(t_object *);

#endif
