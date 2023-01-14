











#include "RT.h"

void	plane_intersection(t_ray ray, void *plane, t_world *world)
{
	t_intersect	temp;

	temp.shape = *(t_object *)plane;
	ray = ray_transform(&ray, &((t_sphere *)plane)->transform.inverse);
	if (EPSILON > ray.direction.tuple.units.y \
		&& ray.direction.tuple.units.y > -EPSILON)
		return ;
	temp.time = -ray.origin.tuple.units.y / ray.direction.tuple.units.y;
	if (vec_push(&world->intersections, &temp) == VEC_ERROR)
		handle_errors("vec_push malloc error plane_intersection");
}
