











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
	computations->over_point = tuple_add(computations->point, \
		tuple_scale(computations->vectors.surface_normal, EPSILON));
	computations->reflectv = reflect(ray.direction, \
		computations->vectors.surface_normal);
	computations->under_point = tuple_sub(computations->point, \
		tuple_scale(computations->vectors.surface_normal, EPSILON));
}

void	compute_refraction_index(t_world *world, t_comp *computation)
{
	t_vec	*containers;
	int	i;
	t_intersect *current;

	i = 0;
	if (vec_new(&containers, 1, sizeof(t_fl)) != VEC_SUCCESS)
		handle_error("unable to malloc for containers vector");

	while (i < world->intersections.len)
	{
		current = vec_get(&world->intersections, i);
		if (current->time == world->hit.intersection.time)
		{
			if (containers->len == 1)
				computation->n1 = 1.0;
			else
				computation->n1 = (t_fl *)vec_get(&containers, containers->len - 1);
		}
	}
	free (containers);
}