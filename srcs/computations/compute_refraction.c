#include "RT.h"

static void	check_container(t_vec *container, t_intersect *current)
{
	int			check;
	uint64_t	j;

	check = false;
	j = 0;
	while (j < container->len)
	{
		if (current->shape->shape_id == \
			((t_intersect *)vec_get(container, j))->shape->shape_id)
		{
			if (vec_remove(container, j) != VEC_SUCCESS)
				handle_errors("unable to remove object from container");
			check = true;
		}
		j++;
	}
	if (check == false)
		if (vec_push(container, current) != VEC_SUCCESS)
			handle_errors("unable to add object to container");
}

void	compute_refraction_index(t_world *world)
{
	t_vec		container;
	uint64_t	i;
	t_intersect	*current;

	i = 0;

	vec_new(&container, 1, sizeof(t_intersect));
	while (i < world->intersections.len)
	{
		current = (t_intersect *)vec_get(&world->intersections, i++);
		if (current->time == world->hit.intersection.time)
		{
			if (container.len == 0)
				world->hit.computations.n1 = 1.0;
			else
				world->hit.computations.n1 = \
					((t_intersect *)vec_get(&container, \
					container.len - 1))->material.refractive_index;
		}
		check_container(&container, current);
		if (current->time == world->hit.intersection.time)
		{
			if (container.len == 0)
				world->hit.computations.n2 = 1.0;
			else
				world->hit.computations.n2 = \
					((t_intersect *)vec_get(&container, \
					container.len - 1))->material.refractive_index;
		}
	}
	vec_free (&container);
}
