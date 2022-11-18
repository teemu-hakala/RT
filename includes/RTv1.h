/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:17:08 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/18 14:15:24 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <math.h>
# include <mlx.h>
# include <stdint.h>
# include <stdio.h>
# include "libft.h"
# include "tuple.h"
# include "matrices.h"
# include "colour_and_light.h"
# include "objects.h"
# include "patterns.h"
# include "world.h"
# include "parse.h"

# define USAGE "<instructions>"
# define WIDTH 401
# define HEIGHT 401
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

/*tuple operations & matrix maths*/
t_tuple	point(t_fl x, t_fl y, t_fl z);
t_tuple	vector(t_fl x, t_fl y, t_fl z);
t_tuple	tuple_add(t_tuple a, t_tuple b);
t_tuple	tuple_sub(t_tuple a, t_tuple b);
t_tuple	tuple_multi(t_tuple a, t_tuple b);
t_tuple	tuple_scale(t_tuple a, t_fl scalar);
t_tuple	tuple_div(t_tuple a, t_fl scalar);
t_fl	magnitude(t_tuple a);
t_tuple	normalize(t_tuple a);
t_fl	dot_product(t_tuple a, t_tuple b);
t_tuple	cross_product(t_tuple a, t_tuple b);
int		matrix_comparison(t_fl **a, t_fl **b, uint32_t size);
t_tuple	matrix_tuple_multi(t_mtx *mtx, t_tuple *tuple);
void	matrix_multi_square(t_mtx *mtx, t_mtx *transformation, uint32_t size);
t_mtx	transpose_matrix(t_mtx *mtx);
t_mtx	identity_matrix(void);
t_fl	determinant(t_mtx *mtx, uint32_t size);
void	matrix_inversion(t_mtx *mtx, uint32_t size);


/* matrix transformations */
void	rotate(t_mtx *mtx, t_tuple *rotations);
void	translate(t_mtx *mtx, t_tuple *transform);
void	scale(t_mtx *mtx, t_tuple *transform);
void	rot_x(t_mtx *mtx, t_fl angle);
void	rot_y(t_mtx *mtx, t_fl angle);
void	rot_z(t_mtx *mtx, t_fl angle);

/* matrix support */
void	identity_matrix_set(t_mtx *dst);

/* ray transformations */
t_ray	ray_translation(t_ray ray, t_tuple transform);
t_ray	ray_scale(t_ray ray, t_tuple transform);
t_ray	ray_transform(t_ray *ray, t_mtx *transform);
t_tuple	hit_position(t_ray *ray, t_fl distance);

/* error handle*/
void	handle_errors(char *str);

/* initialise */
void	open_scene_into(t_win *win, const char *str);
void	initialise_world(t_world *world);
void	initialise_window(t_win *win);

/* handle input*/
int		handle_input(int key);

/* colour and lighting*/
t_tuple		hex_to_tuple_colour(uint32_t colour);
uint32_t	clamped_rgb_to_hex(t_colour *colour);
t_tuple		 shade_hit(t_world *world);
t_tuple		lighting(t_material material, t_light *light, t_phong vectors,
	t_tuple point);
void	is_shadow(t_world *world, t_tuple point, t_light *light);

/* object intialisation */
t_object	sphere(t_tuple origin, t_transform transform, t_material material);
t_object	cylinder(t_tuple origin, t_transform transform, t_material material);
t_object	cone(t_tuple origin, t_transform transform, t_material material);
t_object	plane(t_tuple origin, t_transform transform, t_material material);
t_tuple		plane_origin(void);
t_transform	plane_transform(void);
t_material	plane_material(void);

t_transform	plane_transform_floor(void);
t_transform	plane_transform_right_wall(void);
t_transform	plane_transform_left_wall(void);
t_material	plane_material_floor(void);
t_material	plane_material_right_wall(void);
t_material	plane_material_left_wall(void);

/* object intersection */
void	intersect_world(t_world *world, t_ray ray);
void	identify_hit(t_world *world, t_hit *hit);
void	sphere_intersection(t_ray ray, void *sphere, t_world *world);
int		check_cap(t_ray *ray, t_fl time, t_fl radius);
void	intersect_cylinder_caps(t_object *cylinder, t_ray *ray, t_world *world);
void	cylinder_intersection(t_ray ray, void *cylinder, t_world *world);
void	plane_intersection(t_ray ray, void *plane, t_world *world);
void	intersect_cone_caps(t_object *cone, t_ray *ray, \
	t_world *world);
void	prepare_object(t_world *world, t_object *object, t_comp *computations);

/* reflections*/
t_tuple	reflect(t_tuple input, t_tuple normal);

/* object transformation */
void	transform_object(t_transform *object);

/* view transfrom */
t_mtx	view_transform(t_tuple from, t_tuple to, t_tuple up);

/* normals */
t_tuple	normal_at(void *object, t_tuple *point);
t_tuple	normal_at_sphere(void *sphere, t_tuple *point_at);
t_tuple	normal_at_cylinder(void *cylinder, t_tuple *point_at);
t_tuple	normal_at_cone(void *cone, t_tuple *point_at);

/* plot pixels */
void	render(t_win *win, t_camera *camera);
void	img_pixel_put(t_win *win, int x, int y, unsigned int colour);

/* testing */
void	ft_print_mtx(t_mtx *mtx);
void	default_world(t_world *world);
void	sphere_world(t_world *world);
void	simple_world(t_world *world);
t_transform	default_transform(void);

/* camera */
t_camera	camera(t_tuple origin, t_transform transform, t_fl field_of_view, t_canvas size);
t_ray	ray_for_pixel(t_camera *camera, t_canvas position);
void	prepare_computations(t_world *world);
t_tuple	colour_at(t_world *world);
t_fl	get_pixel_size(t_camera *camera, t_canvas size, t_fl field_of_view);

/* default functions*/
t_tuple	default_origin(void);
t_material	default_phong_mat(void);
t_transform	default_transform(void);
t_transform	default_transform_1(void);
t_transform	default_transform_2(void);

/* patterns*/
typedef void	(*t_pattern_at_fn)(t_material *, t_tuple *);
void	pattern_at(t_material *material, t_tuple *point, t_transform transform);
t_pattern_colours	set_pattern_colours(t_tuple a, t_tuple b);
void	pattern_world(t_world *world);
t_pattern	default_stripe_pattern(void);
t_pattern	default_gradient_pattern(void);
t_pattern	default_ring_pattern(void);
t_pattern	default_checkered_pattern(void);
void	none_at(t_material *material, t_tuple *point);
void	striped_at(t_material *material, t_tuple *point);
void	checkered_at(t_material *material, t_tuple *point);
void	circle_at(t_material *material, t_tuple *point);
void	gradient_at(t_material *material, t_tuple *point);

/* parsing */
void	open_scene_into(t_win *win, const char *str);
double	rt_atof(t_parser *parser);
int		rt_atoi(t_parser *parser);
#endif
