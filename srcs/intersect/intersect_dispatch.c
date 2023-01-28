











#include "RT.h"

static int	sort_intersections(void *xs_a, void *xs_b)
{
	t_intersect	*a;
	t_intersect	*b;
	t_fl		diff;

	a = (t_intersect *)xs_a;
	b = (t_intersect *)xs_b;
	diff = a->time - b->time;
	if (diff > EPSILON)
		return (1);
	else if (diff < EPSILON)
		return (-1);
	else
		return (0);
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

t_intersect set_intersect_info(t_material material, t_appearance appearance, \
	t_transform transform, t_uv_map (*f)(t_tuple *))
{
	return ((t_intersect){
		.material = material,
		.appearance = appearance,
		.transform = transform,
		.f = f
	});
}

void	intersect_world(t_world *world, t_ray ray)
{
	static const t_intersect_function	\
					intersect_object[] = \
	{
		plane_intersection,
		sphere_intersection,
		cone_intersection,
		cylinder_intersection,
		cube_intersection
	};
	uint64_t		i;

	i = (uint64_t)(-1);
	while (++i < world->objects.len)
	{
		intersect_object[((t_object *)vec_get(&world->objects, \
			i))->type](ray, ((t_object *)vec_get(&world->objects, i)), world);
	}
	vec_sort(&world->intersections, sort_intersections);
}
