











#include "RT.h"

t_tuple	reflect(t_tuple input, t_tuple normal)
{
	return (tuple_sub(input,
			tuple_scale(normal, 2 * dot_product(input, normal))));
}

t_ray	ray(t_tuple origin, t_tuple reflectv)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = normalize(reflectv);
	return (ray);
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

t_tuple	reflected_colour(t_world *world, t_comp *computations)
{
	(void)computations;
	t_tuple	reflected_colour;
	t_fl	reflective;

	reflective = world->hit.intersection.material.reflectiveness;
	reflected_colour = point(0, 0, 0);
	if (world->lifetime-- <= 0)
		return (reflected_colour);
	if (reflective < EPSILON)
		return (reflected_colour);
	world->reflected_ray = \
		ray(world->hit.computations.over_point, world->hit.computations.reflectv);
	reflected_colour = colour_at(world, world->reflected_ray);
	return (tuple_scale(reflected_colour,reflective));
}

