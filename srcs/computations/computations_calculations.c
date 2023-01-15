











#include "RT.h"

static t_tuple	hit_position(t_ray *ray, t_fl distance)
{
	return (tuple_add(ray->origin, tuple_scale(ray->direction, distance)));
}

void	prepare_object(t_world *world, t_object *object, t_comp *computations, \
	t_ray ray)
{
	computations->time = world->hit.intersection.time;
	computations->point = hit_position(&ray, computations->time);
	computations->vectors.eye = tuple_scale(ray.direction, -1);
	computations->vectors.surface_normal = \
		normal_at(object, &computations->point);
	if (dot_product(computations->vectors.surface_normal, \
		computations->vectors.eye) < 0)
	{
		computations->inside = true;
		computations->vectors.surface_normal = \
			tuple_scale(computations->vectors.surface_normal, -1);
	}
	else
		computations->inside = false;
	if (get_material(object)->negative == false)
		computations->over_point = tuple_add(computations->point, \
			tuple_scale(computations->vectors.surface_normal, EPSILON));
	else
		computations->over_point = tuple_add(computations->point, \
			tuple_scale(computations->vectors.surface_normal, -EPSILON));
	computations->over_point_parellel_light = \
		tuple_add(computations->point, \
			tuple_scale(computations->vectors.surface_normal, -EPSILON));
	computations->reflectv = reflect(ray.direction, \
		computations->vectors.surface_normal);
}
