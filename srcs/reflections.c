











#include "RT.h"

t_tuple	reflect(t_tuple input, t_tuple normal)
{
	return (tuple_sub(input,
			tuple_scale(normal, 2 * dot_product(input, normal))));
}

t_ray	ray(t_tuple origin, t_tuple reflectv)
{

	t_ray ray;
	ray.origin = origin;
	ray.direction = reflectv;
	return (ray);
	// t_tuple		direction;

	// direction = normalize(tuple_sub(origin, reflectv));
	// return ((t_ray){.origin = origin, .direction = direction});
}

void	is_shadow(t_world *world, t_tuple point, t_light *light)
{
	t_tuple	temp;
	t_tuple	direction;
	t_fl	distance;
	t_ray	ray;

	temp = tuple_sub(light->position, point);
	distance = magnitude(temp);
	direction = normalize(temp);
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
int midasdsaasddsaadsasd;
t_tuple reflected_colour(t_world *world, t_comp *computations)
{
	t_tuple	reflected_colour;

	reflected_colour = point(0, 0 ,0);
	if (world->lifetime-- <= 0)
		return (reflected_colour);
	if (computations->reflective < EPSILON && computations->reflective > -EPSILON)
		return (reflected_colour);
	world->reflected_ray = ray(computations->over_point, computations->reflectv);
	if (0 && midasdsaasddsaadsasd)
	{
		printf("computations->reflectv: %f, %f, %f\n", computations->reflectv.array[0], computations->reflectv.array[1], computations->reflectv.array[2]);
		// printf("intersection shape type: %i\n", world->hit.intersection.shape->type);
		// printf("over_point: %f, %f, %f, %f\n", world->hit.computations.over_point.array[0], world->hit.computations.over_point.array[1], world->hit.computations.over_point.array[2], world->hit.computations.over_point.array[3]);
	}
	reflected_colour = colour_at(world, world->reflected_ray);
	return (tuple_scale(reflected_colour, computations->reflective));
}
