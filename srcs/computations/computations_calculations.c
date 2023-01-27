






#include "RT.h"

static t_tuple	hit_position(t_ray *ray, t_fl distance)
{
	return (tuple_add(ray->origin, tuple_scale(ray->direction, distance)));
}

void	prepare_object(t_world *world, t_object *object, t_comp *computations, \
	t_ray ray)
{
	(void)computations;
	world->hit.computations.time = world->hit.intersection.time;
	world->hit.computations.point = hit_position(&ray, world->hit.computations.time);
	world->hit.computations.vectors.eye = tuple_scale(ray.direction, -1);
	world->hit.computations.vectors.surface_normal = \
		normal_at(object, &world->hit.computations.point);
	if (dot_product(world->hit.computations.vectors.surface_normal, \
		world->hit.computations.vectors.eye) < 0)
	{
		world->hit.computations.inside = true;
		world->hit.computations.vectors.surface_normal = \
			tuple_scale(world->hit.computations.vectors.surface_normal, -1);
	}
	else
		world->hit.computations.inside = false;
	world->hit.computations.over_point = tuple_add(world->hit.computations.point, \
		tuple_scale(world->hit.computations.vectors.surface_normal, EPSILON));
	world->hit.computations.reflectv = reflect(ray.direction, \
		world->hit.computations.vectors.surface_normal);
	compute_refraction_index(world, computations);
	world->hit.computations.under_point = tuple_sub(world->hit.computations.point, \
		tuple_scale(world->hit.computations.vectors.surface_normal, EPSILON));
}
