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
			((t_container *)vec_get(container, j))->shape_id)
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

void	compute_refraction_index(t_world *world, t_comp *computation)
{
	t_vec		container;
	uint64_t	i;
	t_intersect *current;

	i = 0;
	vec_new(&container, 1, sizeof(t_container));
	while (i < world->intersections.len)
	{
		current = vec_get(&world->intersections, i);
		if (current->time == world->hit.intersection.time)
		{
			if (container.len == 0)
				computation->n1 = 1.0;
			else
				computation->n1 = ((t_container *)vec_get(&container, \
					container.len - 1))->material.refractive_index;
		}
		check_container(&container, current);
		if (current->time == world->hit.intersection.time)
		{
			if (container.len == 0)
				computation->n2 = 1.0;
			else
				computation->n2 = ((t_container *)vec_get(&container, \
					container.len - 1))->material.refractive_index;
		}
		i++;
	}
	vec_free (&container);
}
