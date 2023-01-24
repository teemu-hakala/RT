











#ifndef WORLD_H
# define WORLD_H
# include "RT.h"
/*inside == true if hit occurs inside object, false otherwise. If hit occurs
iside object, normal vector is inverted*/

typedef struct s_quadratic
{
	t_fl	a;
	t_fl	b;
	t_fl	c;
	t_fl	discriminant;
	t_fl	res_1;
	t_fl	res_2;
}				t_quadratic;

typedef struct s_intersect
{
	t_fl		time;
	t_object	*shape;
	t_fl		shape_id;
	t_material	material;
}				t_intersect;

typedef struct s_hit
{
	t_intersect	intersection;
	t_comp		computations;
	int			hit_check;
}	t_hit;

typedef struct s_ray
{
	t_tuple	origin;
	t_tuple	direction;
}			t_ray;

typedef struct s_world
{
	t_camera	camera;
	t_vec		lights;
	t_vec		objects;
	t_vec		intersections;
	t_hit		hit;
	t_hit		shadow_hit;
	t_ray		ray;
	t_ray		reflected_ray;
	t_ray		refracted_ray;
	int			lifetime;
	int			refraction_lifetime;
}	t_world;

#endif
