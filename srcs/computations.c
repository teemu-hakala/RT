#include "RTv1.h"

void	prepare_object(t_world *world, t_object *object, t_comp *computations)
{
	computations->time = world->hit.intersection->time;
	computations->point = hit_position(&world->ray, computations->time);
	computations->vectors.eye = tuple_scale(world->ray.direction, -1);
	computations->vectors.surface_normal = \
		normal_at(object, &computations->point);
	if (dot_product(computations->vectors.surface_normal, \
		computations->vectors.eye) < 0)
	{
		computations->inside = 1;
		computations->vectors.surface_normal = \
			tuple_scale(computations->vectors.surface_normal, -1);
	}
	else
		computations->inside = 0;
}

void	prepare_plane(t_world *world)
{
	prepare_object(world, world->hit.intersection->shape, \
		&world->hit.computations);
}

void	prepare_sphere(t_world *world)
{
	prepare_object(world, world->hit.intersection->shape, \
		&world->hit.computations);
}

void	prepare_cone(t_world *world)
{
	prepare_object(world, world->hit.intersection->shape, \
		&world->hit.computations);
}

void	prepare_cylinder(t_world *world)
{
	prepare_object(world, world->hit.intersection->shape, \
		&world->hit.computations);
}

void	prepare_computations(t_world *world)
{
	static const t_computation_fn	\
			precompute_shape[] = {
		prepare_plane,
		prepare_sphere,
		prepare_cone,
		prepare_cylinder
	};

	precompute_shape[world->hit.intersection->shape->type - OBJECT_INDEX_OFFSET]
		(world);
}
