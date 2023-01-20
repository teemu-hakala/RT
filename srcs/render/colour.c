











#include "RT.h"

t_tuple	get_final_colour(t_world *world, t_ray ray, \
	t_tuple colour_static_object, t_tuple *colour_final)
{
	t_tuple	colour_moving_object;
	t_fl	time;

	time = 0;
	while (++world->camera.shutter.count < SHUTTER_COUNT + 1)
	{
		vec_clear(&world->intersections);
		intersect_world_at_time(world, ray, time);
		identify_hit(world, &world->hit);
		if (world->hit.hit_check == true)
		{
			prepare_computations(world, ray);
			colour_moving_object = tuple_div(shade_hit(world), \
				SHUTTER_COUNT + 1); // check!
			*colour_final = tuple_add(*colour_final, colour_moving_object);
		}
		else
		{
			*colour_final = tuple_add(*colour_final, colour_static_object);
		}
		time += world->camera.shutter.step;
	}
}

t_tuple	colour_at(t_world *world, t_ray ray)
{
	t_tuple	colour_static_object;
	t_tuple	colour_final;

	world->camera.shutter.count = 0;
	vec_clear(&world->intersections);
	intersect_world(world, ray);
	identify_hit(world, &world->hit);
	if (world->hit.hit_check == true)
	{
		prepare_computations(world, ray);
		colour_static_object = tuple_div(shade_hit(world), \
				SHUTTER_COUNT + 1); // check
		get_final_colour(world, ray, colour_static_object, &colour_final);
		return (apply_filter(world, colour_final));
	}
	else
		return (vector(0, 0, 0));
}
