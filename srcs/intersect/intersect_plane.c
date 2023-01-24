











#include "RT.h"

void	plane_intersection(t_ray ray, void *plane, t_world *world)
{
	t_intersect	temp;

	temp.shape = plane;
	temp.shape_id = ((t_object *)plane)->shape_id;
	temp.material = ((t_plane*)plane)->material;
	ray = ray_transform(&ray, &((t_plane *)plane)->transform.inverse);
	if (EPSILON > ray.direction.tuple.units.y \
		&& ray.direction.tuple.units.y > -EPSILON)
		return ;
	temp.time = -ray.origin.tuple.units.y / ray.direction.tuple.units.y;
	if (vec_push(&world->intersections, &temp) == VEC_ERROR)
		handle_errors("vec_push malloc error plane_intersection");
}
