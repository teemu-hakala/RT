











#include "RT.h"

t_tuple	reflect(t_tuple input, t_tuple normal)
{
	return (tuple_sub(input,
			tuple_scale(normal, 2 * dot_product(input, normal))));
}

static void	direction_and_distance(t_light *light, t_tuple *direction,
	t_tuple point, t_fl *distance)
{
	t_tuple	temp;

	if (light->type == LIGHT_SPOT)
	{
		temp = tuple_sub(light->position, point);
		*distance = magnitude(temp);
	}
	else
	{
		temp = normalize(light->direction);
		*distance = -INFINITY;
	}
	*direction = normalize(temp);
}

void	is_shadow(t_world *world, t_tuple point, t_light *light)
{
	t_tuple	direction;
	t_fl	distance;
	t_ray	ray;

	direction_and_distance(light, &direction, point, &distance);
	ray = (t_ray){point, direction};
	vec_clear(&world->intersections);
	intersect_world(world, ray);
	identify_hit(world, &world->shadow_hit);
	world->hit.computations.vectors.in_shadow = false;
	if (world->shadow_hit.hit_check == true)
	{
		if (world->shadow_hit.intersection.time < distance)
		{
			world->hit.computations.vectors.in_shadow = true;
		}
	}
}
