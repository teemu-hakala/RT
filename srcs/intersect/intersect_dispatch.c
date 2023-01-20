











#include "RT.h"

static int	sort_intersections(void *xs_a, void *xs_b)
{
	t_intersect	*a;
	t_intersect	*b;
	t_fl		diff;

	a = (t_intersect *)xs_a;
	b = (t_intersect *)xs_b;
	diff = a->time - b->time;
	if (diff > 0)
		return (1);
	else if (diff == 0)
		return (0);
	else
		return (-1);
}

void	identify_hit(t_world *world, t_hit *hit)
{
	t_intersect	*intersection;
	uint64_t	i;

	i = 0;
	hit->hit_check = false;
	while (i < world->intersections.len)
	{
		intersection = \
			(t_intersect *)vec_get(&world->intersections, i++);
		if (intersection->time >= 0)
		{
			hit->intersection = *intersection;
			hit->hit_check = true;
			break ;
		}
	}
}

void	intersect_world(t_world *world, t_ray ray)
{
	static const t_intersect_function	\
					intersect_object_if[] = \
	{
		plane_intersect_if,
		sphere_intersect_if,
		cone_intersect_if,
		cylinder_intersect_if,
		cube_intersect_if
	};
	uint64_t		i;

	i = (uint64_t)(-1);
	while (++i < world->objects.len)
	{
		intersect_object_if[((t_object *)vec_get(&world->objects, \
			i))->type - OBJECT_INDEX_OFFSET] \
			(ray, ((t_object *)vec_get(&world->objects, \
			i)), world);
	}
	vec_sort(&world->intersections, sort_intersections);
}
