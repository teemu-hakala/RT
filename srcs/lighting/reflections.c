











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
		// temp = tuple_scale(light->direction, -1); // tuple_scale resets .w to VECTOR_0
		temp = tuple_scale(light->direction, 1);
		temp.array[W] = VECTOR_0;
		*distance = INFINITY;
	}
	*direction = normalize(temp);
}

void	is_shadow(t_world *world, t_tuple point, t_light *light)
{
	t_tuple	direction;
	t_fl	distance;
	t_ray	ray;

	direction_and_distance(light, &direction, point, &distance);
	ray = (t_ray){.origin = point, .direction = direction};
	// if (light->type != LIGHT_SPOT)
	// 	ray.origin = world->hit.computations.over_point_parellel_light;
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
	t_tuple	reflected_colour;

	reflected_colour = point(0, 0, 0);
	if (world->lifetime-- <= 0)
		return (reflected_colour);
	if (computations->reflective < EPSILON)
		return (reflected_colour);
	world->reflected_ray = \
		ray(computations->over_point, computations->reflectv);
	reflected_colour = colour_at(world, world->reflected_ray);
	return (tuple_scale(reflected_colour, computations->reflective));
}
