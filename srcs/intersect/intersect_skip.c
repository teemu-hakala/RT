











#include "RT.h"

void	plane_intersect_if(t_ray ray, void *object, t_world *world)
{
	if (!tuple_nearly_equals(((t_plane *)object)->movement.velocity, \
		vector(0, 0, 0)))
		return ;
	plane_intersection(ray, object, world);
}

void	sphere_intersect_if(t_ray ray, void *object, t_world *world)
{
	if (!tuple_nearly_equals(((t_sphere *)object)->movement.velocity, \
		vector(0, 0, 0)))
		return ;
	sphere_intersection(ray, object, world);
}

void	cone_intersect_if(t_ray ray, void *object, t_world *world)
{
	if (!tuple_nearly_equals(((t_cone *)object)->movement.velocity, \
		vector(0, 0, 0)))
		return ;
	cone_intersection(ray, object, world);
}

void	cylinder_intersect_if(t_ray ray, void *object, t_world *world)
{
	if (!tuple_nearly_equals(((t_cylinder *)object)->movement.velocity, \
		vector(0, 0, 0)))
		return ;
	cylinder_intersection(ray, object, world);
}

void	cube_intersect_if(t_ray ray, void *object, t_world *world)
{
	if (!tuple_nearly_equals(((t_cube *)object)->movement.velocity, \
		vector(0, 0, 0)))
		return ;
	cube_intersection(ray, object, world);
}
