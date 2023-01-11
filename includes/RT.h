











#ifndef RT_H
# define RT_H

# include <math.h>
# include <mlx.h>
# include <stdint.h>
# include "libft.h"
# include "tuple.h"
# include "matrices.h"
# include "colour_and_light.h"
# include "objects.h"
# include "patterns.h"
# include "world.h"
# include "parse.h"
# include <stdio.h>

# define USAGE "./RT ./scenes/[.json file]"
# define WIDTH 800
# define HEIGHT 400
# define WALL_WIDTH 7
# define WALL_HEIGHT 7
# define KEY_DOWN 2
# define ESC 53
# define MOUSE_ESC 17
# define EPSILON 0.00001
# define PLANE_EPSILON 0.00001
# define TUPLE_EPSILON 0.00001

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		length;
	int		endian;
}	t_img;

typedef struct s_coords
{
	uint32_t	row;
	uint32_t	col;
}				t_coords;

typedef struct s_pixel_index
{
	t_fl		row;
	t_fl		col;
}				t_index;

typedef struct s_win
{
	t_img		img;
	void		*mlx;
	void		*win;
	int			fd;
	t_world		world;
}	t_win;

typedef void	(*t_intersect_function)(t_ray, void *, t_world *);

typedef void	(*t_shading_function)(t_world *, void *, t_tuple *, t_light *);

typedef void	(*t_computation_fn)(t_world *);

typedef void	(*t_pattern_at_fn)(t_pattern *, t_tuple *, t_tuple *);

typedef void	(*t_texture_at_fn)(t_texture *, t_uv_map *, t_tuple *);

/*tuple operations & matrix maths*/
t_tuple		point(t_fl x, t_fl y, t_fl z);
t_tuple		vector(t_fl x, t_fl y, t_fl z);
t_tuple		tuple_add(t_tuple a, t_tuple b);
t_tuple		tuple_sub(t_tuple a, t_tuple b);
t_tuple		tuple_multi(t_tuple a, t_tuple b);
t_tuple		tuple_scale(t_tuple a, t_fl scalar);
t_tuple		tuple_div(t_tuple a, t_fl scalar);
t_fl		magnitude(t_tuple a);
t_tuple		normalize(t_tuple a);
t_fl		dot_product(t_tuple a, t_tuple b);
t_tuple		cross_product(t_tuple a, t_tuple b);
t_tuple		matrix_tuple_multi(t_mtx *mtx, t_tuple *tuple);
void		matrix_multi_square(t_mtx *mtx, t_mtx *transformation, \
			uint32_t size);
t_mtx		transpose_matrix(t_mtx *mtx);
t_mtx		identity_matrix(void);
t_fl		determinant(t_mtx *mtx, uint32_t size);
void		matrix_inversion(t_mtx *mtx, uint32_t size);

/* matrix transformations */
void		rotate(t_mtx *mtx, t_tuple *rotations);
void		translate(t_mtx *mtx, t_tuple *transform);
void		scale(t_mtx *mtx, t_tuple *transform);

/* matrix support */
void		identity_matrix_set(t_mtx *dst);

/* ray transformations */
t_ray		ray_transform(t_ray *ray, t_mtx *transform);

/* error handle*/
void		handle_errors(char *str);

/* initialise */
void		initialise_world(t_world *world);
void		initialise_window(t_win *win);

/* handle input*/
int			handle_input(int key);

/* colour and lighting*/
t_tuple		hex_to_tuple_colour(uint32_t colour);
uint32_t	clamped_rgb_to_hex(t_colour *colour);
t_tuple		lighting(t_info *lighting_info, t_light *light, t_phong vectors,
				t_tuple point);
void		is_shadow(t_world *world, t_tuple point, t_light *light);
t_tuple		reflect(t_tuple input, t_tuple normal);

/* shading */
t_tuple		shade_hit(t_world *world);
void		shade_plane(t_world *world, void *plane, t_tuple *colour,
				t_light *light);
void		shade_sphere(t_world *world, void *sphere, t_tuple *colour,
				t_light *light);
void		shade_cone(t_world *world, void *cone, t_tuple *colour,
				t_light *light);
void		shade_cylinder(t_world *world, void *cylinder, t_tuple *colour,
				t_light *light);
void		shade_cube(t_world *world, void *cube, t_tuple *colour,
				t_light *light);

/* object intersection */
void		intersect_world(t_world *world, t_ray ray);
void		plane_intersection(t_ray ray, void *plane, t_world *world);
void		sphere_intersection(t_ray ray, void *sphere, t_world *world);
void		cone_intersection(t_ray ray, void *cone, t_world *world);
void		cylinder_intersection(t_ray ray, void *cylinder, t_world *world);
int			check_cap(t_ray *ray, t_fl time, t_fl radius);
void		cube_intersection(t_ray ray, void *cube, t_world *world);
t_fl		max_double(t_fl x, t_fl y, t_fl z);
void		identify_hit(t_world *world, t_hit *hit);

/*computations*/
void		prepare_object(t_world *world, t_object *object, \
			t_comp *computations);
void		prepare_plane(t_world *world);
void		prepare_sphere(t_world *world);
void		prepare_cone(t_world *world);
void		prepare_cylinder(t_world *world);
void		prepare_cube(t_world *world);

/* reflections*/

/* object transformation */
void		transform_object(t_transform *object);

/* view transfrom */
t_mtx		view_transform(t_tuple from, t_tuple to, t_tuple up);

/* normals */
t_tuple		object_to_world_space(t_mtx *inverse, t_tuple obj_space);
t_tuple		normal_at(void *object, t_tuple *point);
t_tuple		normal_at_plane(void *plane, t_tuple *point_at);
t_tuple		normal_at_sphere(void *sphere, t_tuple *point_at);
t_tuple		normal_at_cone(void *cone, t_tuple *point_at);
t_tuple		normal_at_cylinder(void *cylinder, t_tuple *point_at);
t_tuple		normal_at_cube(void *cube, t_tuple *point_at);

/* plot pixels */
void		render(t_win *win, t_camera *camera);
void		img_pixel_put(t_win *win, int x, int y, unsigned int colour);

/* camera */
t_ray		ray_for_pixel(t_camera *camera, t_canvas position);
void		prepare_computations(t_world *world);
t_tuple		colour_at(t_world *world);
t_fl		get_pixel_size(t_camera *camera, t_canvas size, t_fl field_of_view);

/* default patterns*/
t_pattern	default_vertical_stripe_pattern(void);
t_pattern	default_horizontal_stripe_pattern(void);
t_pattern	default_gradient_pattern(void);
t_pattern	default_ring_pattern(void);
t_pattern	default_simple_checkered_pattern(void);
t_pattern	default_pattern(void);

/* default textures*/
t_texture	default_texture(void);
t_texture	default_checkered_texture(void);
t_texture	default_align_check(void);
t_texture	default_external(void);

t_tuple	get_appearance_colour(t_appearance *appearance, t_transform transform,
t_tuple *p);

/* patterns*/
t_tuple		pattern_at(t_pattern *pattern, \
			t_transform transform, t_tuple *point);
void		none_at(t_pattern *pattern, t_tuple *point, t_tuple *colour);
void		vertical_striped_at(t_pattern *pattern, t_tuple *point, t_tuple *colour);
void		horizontal_striped_at(t_pattern *pattern, t_tuple *point, t_tuple *colour);
void		simple_checkered_at(t_pattern *pattern, t_tuple *point, t_tuple *colour);
void		circle_at(t_pattern *pattern, t_tuple *point, t_tuple *colour);
void		gradient_at(t_pattern *pattern, t_tuple *point, t_tuple *colour);

/*textures*/
t_tuple		texture_at(t_texture *texture, t_uv_map *map);
void		no_texture_at(t_texture *texture, t_uv_map *map, t_tuple *colour);
void		checkered_at(t_texture *texture, t_uv_map *map, t_tuple *colour);
void		align_check_at(t_texture *texture, t_uv_map *map, t_tuple *colour);
void		external_at(t_texture *texture, t_uv_map *map, t_tuple *colour);
t_tuple		transform_point(t_tuple *point, t_transform *shape_transform, \
			t_transform *pattern_transform);
t_uv_map	spherical_map(t_tuple *p);
t_uv_map	planar_map(t_tuple *p);
t_uv_map	cylindrical_map(t_tuple *p);
t_uv_map	conical_map(t_tuple *p);
t_uv_map	cubic_map(t_tuple *p, t_texture *texture);

int			face_from_point(t_tuple *p);
t_uv_map	cube_uv_right(t_tuple *p);
t_uv_map	cube_uv_up(t_tuple *p);
t_uv_map	cube_uv_down(t_tuple *p);

/* parsing */
double		rt_atof(t_parser *parser);
int			rt_atoi(t_parser *parser);

#endif
